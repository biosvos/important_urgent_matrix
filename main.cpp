//
// Created by j on 2022-10-15.
//

#include <nana/gui.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <iostream>
#include <utility>

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

    [[nodiscard]] size_t Size() const {
        return box_.at(0).size();
    }

    [[nodiscard]] std::string Get(int index) const {
        return box_.at(0).at(index).text(0);
    }

private:
    nana::listbox box_;

    void SetSignals() {
        uint64_t selected;
        box_.events().mouse_down([&]() {
            auto sel = box_.selected();
            for (const auto &item: sel) {
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
            if (ho.item + 1 < box_.at(0).size()) {
                box_.insert_item(nana::listbox::index_pair{0, ho.item + 1}, box_.at(0).at(selected).text(0));
            } else {
                box_.at(0).append(box_.at(0).at(selected).text(0));
            }
            if (selected < ho.item) {
                box_.erase(box_.at(0).at(selected));
            } else {
                box_.erase(box_.at(0).at(selected + 1));
            }
        });
    }
};

void ModelGrid(const nana::form &root, ListBox &important_box, ListBox &urgent_box) {
    int length = static_cast<int>(important_box.Size());
    nana::form fm(root, nana::API::make_center(length * 100, length * 100));
    nana::drawing dw(fm);
    dw.draw([&](nana::paint::graphics &graph) {
        for (int x = 0; x < important_box.Size(); ++x) {
            for (int y = 0; y < important_box.Size(); ++y) {
                graph.rectangle(nana::rectangle{100 * x, 100 * y, 100, 100}, false, nana::colors::black);
            }
        }

        std::unordered_map<std::string, int> urgent_map;
        for (int i = 0; i < urgent_box.Size(); ++i) {
            urgent_map[urgent_box.Get(i)] = i;
        }

        for (int i = 0; i < important_box.Size(); ++i) {
            int x = static_cast<int>(100 * (important_box.Size() - i - 1));
            graph.string(nana::point{x, 100 * urgent_map[important_box.Get(i)]},
                         important_box.Get(i));
        }
    });

    fm.collocate();
    fm.modality();
}

int main() {
    nana::form fm;
    nana::place place(fm);
    place.div("<vert "
              "<<important><urgent>><fit <fit add><fit view> >"
              ">");
    ListBox important_box(fm, "important");
    place["important"] << important_box.GetReference();
    ListBox urgent_box(fm, "urgent");
    place["urgent"] << urgent_box.GetReference();
    nana::button add_button(fm, "Add");
    place["add"] << add_button;
    nana::button view_button(fm, "View");
    place["view"] << view_button;
    place.collocate();

    for (auto value: {"AA", "BB", "CC", "DD"}) {
        important_box.Append(value);
        urgent_box.Append(value);
    }

    add_button.events().click([&]() {
        nana::inputbox::text entry("entry");
        nana::inputbox input_box(fm, "description", "ha");
        if (input_box.show(entry)) {
            auto value = entry.value();
            important_box.Append(value);
            urgent_box.Append(value);
        }
    });

    view_button.events().click([&]() {
        ModelGrid(fm, important_box, urgent_box);
    });

    fm.show();
    ModelGrid(fm, important_box, urgent_box);
    nana::exec();
    return 0;
}