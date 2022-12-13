//
// Created by biosvos on 12/12/22.
//

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <utility>

#include "ftx.h"


class ListView {
public:
    explicit ListView(std::function<void(std::string, std::string)> element_position_changed) :
            container_(ftxui::Container::Vertical({})),
            element_position_changed_(std::move(element_position_changed)) {
        BuildShortcut();
    }

    void Add(const std::string &name) {
        components_.emplace_back(name, ftxui::Button(name, [] {}, button_style_));
        Refresh();
    }

    void Erase(const std::string &name) {
        components_.erase(std::find_if(components_.begin(), components_.end(),
                                       [&name](const std::pair<std::string, ftxui::Component> &item) {
                                           return item.first == name;
                                       }));
        Refresh();
    }

    ftxui::Component GetComponent() {
        return shortcut_;
    }

private:
    void Refresh() {
        container_->DetachAllChildren();
        for (const auto &item: components_) {
            container_->Add(item.second);
        }
    }

    void BuildShortcut() {
        shortcut_ = ftxui::CatchEvent(container_, [&](const ftxui::Event &event) {
            if (event == key_ctrl_up_) { // Ctrl + Up
                auto pos = GetFocusedElementIndex();
                if (pos == 0) {
                    return false;
                }

                std::swap(components_[pos], components_[pos - 1]);
                Refresh();
                components_[pos - 1].second->TakeFocus();
                element_position_changed_(components_[pos].first, components_[pos - 1].first);
                return true;
            }
            if (event == key_ctrl_down_) { // Ctrl + Down
                auto pos = GetFocusedElementIndex();
                if (pos == components_.size() - 1) {
                    return false;
                }

                std::swap(components_[pos], components_[pos + 1]);
                Refresh();
                components_[pos + 1].second->TakeFocus();
                element_position_changed_(components_[pos].first, components_[pos + 1].first);
                return true;
            }
            return false;
        });
    }

    size_t GetFocusedElementIndex() {
        for (int i = 0; i < components_.size(); ++i) {
            if (components_[i].second->Focused()) {
                return i;
            }
        }
        throw std::runtime_error("발생 안해야한다.");
    }

    inline static auto button_style_ = ftxui::ButtonOption::Animated(ftxui::Color::Default,
                                                                     ftxui::Color::GrayDark,
                                                                     ftxui::Color::Default,
                                                                     ftxui::Color::White);
    inline static auto key_ctrl_up_ = ftxui::Event::Special("\x1B[1;5A");
    inline static auto key_ctrl_down_ = ftxui::Event::Special("\x1B[1;5B");

    std::vector<std::pair<std::string, ftxui::Component>> components_;
    ftxui::Component container_;
    ftxui::Component shortcut_;

    std::function<void(std::string, std::string)> element_position_changed_;
};

Ftx::Ftx(const std::shared_ptr<IUsecase> &usecase) : usecase_(usecase) {}

void ShowMatrix(const std::vector<std::string> &important, const std::vector<std::string> &urgent) {
    std::vector<std::vector<ftxui::Element>> matrix;
    for (int i = 0; i < important.size(); ++i) {
        auto &row = matrix.emplace_back();
        for (int j = 0; j < important.size(); ++j) {
            row.emplace_back(ftxui::text("☆") | ftxui::center | ftxui::border);
        }
    }
    std::unordered_map<std::string, size_t> important_map, urgent_map;
    {
        for (int i = 0; i < important.size(); ++i) {
            important_map[important[i]] = i;
        }
    }

    {
        for (int i = 0; i < urgent.size(); ++i) {
            urgent_map[urgent[i]] = i;
        }
    }

    for (const auto &item: important) {
        unsigned long row = urgent_map[item];
        unsigned long col = important.size() - 1 - important_map[item];
        matrix[row][col] =
                ftxui::text(item) | ftxui::border;
    }

    auto gridbox = ftxui::gridbox(matrix);
    auto layout = ftxui::Container::Vertical({

                                             });

    auto renderer = ftxui::Renderer(layout, [&] {
        return ftxui::vbox({
                                   gridbox | ftxui::border
                           });
    });

    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screen.Loop(renderer);
}

void Ftx::Run() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    auto important = ListView([&](const std::string &text, const std::string &dst) {
        usecase_->ChangeImportantOrder(text, dst);
    });
    auto urgent = ListView([&](const std::string &text, const std::string &dst) {
        usecase_->ChangeUrgentOrder(text, dst);
    });

    {
        auto importants = usecase_->ListImportantNotes();
        for (const auto &item: importants) {
            important.Add(item);
        }
    }

    {
        auto urgents = usecase_->ListUrgentNotes();
        for (const auto &item: urgents) {
            urgent.Add(item);
        }
    }

    std::string add_word;
    auto add_input = ftxui::Input(&add_word, "word");
    auto add_button = ftxui::Button("Add", [&] {
        usecase_->CreateNote(add_word);
        important.Add(add_word);
        urgent.Add(add_word);

        add_word.clear();
    });

    auto show_button = ftxui::Button("Show", [&] {
        ShowMatrix(usecase_->ListImportantNotes(), usecase_->ListUrgentNotes());
    });

    auto layout = ftxui::Container::Horizontal({
                                                       important.GetComponent(),
                                                       urgent.GetComponent(),
                                                       ftxui::Container::Vertical({
                                                                                          add_input,
                                                                                          add_button,
                                                                                          show_button
                                                                                  })
                                               });

    auto renderer = ftxui::Renderer(layout, [&] {
        return ftxui::hbox({
                                   ftxui::vbox({
                                                       ftxui::text("important"),
                                                       ftxui::separator(),
                                                       important.GetComponent()->Render() | ftxui::vscroll_indicator |
                                                       ftxui::frame
                                               }) | ftxui::border,
                                   ftxui::vbox({
                                                       ftxui::text("urgent"),
                                                       ftxui::separator(),
                                                       urgent.GetComponent()->Render() | ftxui::vscroll_indicator |
                                                       ftxui::frame
                                               }) | ftxui::border,
                                   ftxui::vbox({
                                                       ftxui::text("add note"),
                                                       ftxui::separator(),
                                                       add_input->Render(),
                                                       add_button->Render(),
                                                       show_button->Render()
                                               }) | ftxui::border
                           });
    });

    screen.Loop(renderer);
}
