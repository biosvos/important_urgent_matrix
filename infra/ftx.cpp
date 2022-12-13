//
// Created by biosvos on 12/12/22.
//

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <utility>

#include "ftx.h"


class ListView {
public:
    explicit ListView(std::function<void(std::string, size_t pos)> element_position_changed) :
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
                element_position_changed_(components_[pos - 1].first, pos - 1);
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
                element_position_changed_(components_[pos + 1].first, pos + 1);
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

    std::function<void(std::string, size_t pos)> element_position_changed_;
};

Ftx::Ftx(const std::shared_ptr<IUsecase> &usecase) : usecase_(usecase) {}

void Ftx::Run() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    auto important = ListView([&](std::string text, size_t pos) {
        usecase_->ChangeImportantOrder(std::move(text), pos);
    });
    auto urgent = ListView([&](std::string text, size_t pos) {
        usecase_->ChangeUrgentOrder(std::move(text), pos);
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

    auto layout = ftxui::Container::Horizontal({
                                                       important.GetComponent(),
                                                       urgent.GetComponent(),
                                                       ftxui::Container::Vertical({
                                                                                          add_input,
                                                                                          add_button
                                                                                  })
                                               });

    auto renderer = ftxui::Renderer(layout, [&]() {
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
                                                       add_button->Render()
                                               }) | ftxui::border
                           });
    });

    screen.Loop(renderer);
}
