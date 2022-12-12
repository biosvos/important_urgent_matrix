//
// Created by biosvos on 12/12/22.
//

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include "ftx.h"

class ListView {
public:
    ListView() : container_(ftxui::Container::Vertical({})) {
        shortcut_ = ftxui::CatchEvent(container_, [&](const ftxui::Event &event) {
            if (event == key_ctrl_up_) { // Ctrl + Up
                auto pos = GetFocusedElementIndex();
                if (pos == 0) {
                    return false;
                }

                std::swap(components_[pos], components_[pos - 1]);
                Refresh();
                components_[pos - 1].second->TakeFocus();
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
                return true;
            }
            return false;
        });
    }

    void Add(const std::string &name) {
        components_.emplace_back(name, ftxui::Button(name, [] {}, button_style_));
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

    std::vector <std::pair<std::string, ftxui::Component>> components_;
    ftxui::Component container_;
    ftxui::Component shortcut_;
};

int main() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    auto important = ListView();
    auto urgent = ListView();
    for (int i = 0; i < 30; ++i) {
        auto text = "Button" + std::to_string(i);
        important.Add(text);
        urgent.Add(text);
    }

    auto layout = ftxui::Container::Horizontal({
                                                       important.GetComponent(),
                                                       urgent.GetComponent()
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
                                               }) | ftxui::border
                           });
    });

    screen.Loop(renderer);
}
