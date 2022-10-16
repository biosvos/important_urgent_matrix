//
// Created by j on 2022-10-15.
//

#include <nana/gui.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <iostream>
#include <utility>

class Items {
public:
    void Append(const std::string &str) {
        items_.push_back(str);
    }

private:
    std::vector<std::string> items_;
};

class ListBox {
public:
    explicit ListBox(nana::form &fm, std::string title) : box_(fm) {
        box_.sortable(false);
        box_.append_header(std::move(title));

        SetSignals();
    }

    [[nodiscard]] const nana::listbox &GetReference() const {
        return box_;
    }

    void Append(const std::string &str) {
        box_.at(0).append(str);
    }

private:
    nana::listbox box_;

    void SetSignals() {
        uint64_t selected;
        box_.events().mouse_down([&]() {
            auto sel = box_.selected();
            for (const auto &item: sel) {
                std::cout << item.item << " " << item.cat << "-> " << std::endl;
                selected = item.item;
            }
        });

        box_.events().mouse_up([&]() {
            auto ho = box_.hovered(false);
            if (ho.item == nana::npos) {
                return;
            }
            if (ho.item + 1 == selected) {
                // 자기 자신이므로 할 이유가 없음
                return;
            }
            if (ho.item == selected) {
                // 자기 자신이므로 할 이유가 없음
                return;
            }
            std::cout << ho.item << " " << ho.cat << std::endl;
            if (ho.item + 1 < box_.at(0).size()) {
                box_.insert_item(nana::listbox::index_pair{0, ho.item + 1}, box_.at(0).at(selected).text(0));
            } else {
                box_.at(0).append(box_.at(0).at(selected).text(0));
            }
//        std::cout <<  << std::endl;
            if (selected < ho.item) {
                box_.erase(box_.at(0).at(selected));
            } else {
                box_.erase(box_.at(0).at(selected + 1));
            }
//        box.at(0).
        });

    }
};

int main() {
    nana::form fm;
    nana::place place(fm);
    place.div("<vert <<important><urgent>><fit button>>");
    ListBox important_box(fm, "important");
    place["important"] << important_box.GetReference();
    ListBox urgent_box(fm, "urgent");
    place["urgent"] << urgent_box.GetReference();
    nana::button button(fm, "Add");
    place["button"] << button;
    place.collocate();

    button.events().click([&]() {
        nana::inputbox::text entry("entry");
        nana::inputbox input_box(fm, "description", "ha");
        if (input_box.show(entry)) {
            auto value = entry.value();
            important_box.Append(value);
            urgent_box.Append(value);
        }
    });

    fm.show();
    nana::exec();
    return 0;
}