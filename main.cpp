//
// Created by j on 2022-10-15.
//

#include <nana/gui.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <iostream>

//void foo(const nana::arg_click &ei) {
//    nana::form fm(ei.window_handle);
////    fm.caption(("I am a modal form"));
////    nana::place place(fm);
////    place.div("<vert <entry><ba bb>>>");
//    nana::inputbox::text entry("entry");
//    nana::inputbox input_box(fm, "description", "ha");
//    input_box.show();
////    place["entry"] << input_box;
////    place.collocate();
////    std::cout << "Block execution till modal form is closed" << std::endl;
//    nana::API::modal_window(fm);
////    std::cout << "modal form is closed" << std::endl;
//}

int main() {
    nana::form fm;
    nana::place place(fm);
    place.div("<vert <list><button>>");
    nana::listbox box(fm);
    place["list"] << box;
    nana::button button(fm, "Add");
    place["button"] << button;
    place.collocate();

    box.events().

    {
        box.append_header("item");
        box.at(0).append("aa");
        box.at(0).append("bb");
        box.at(0).append("cc");
    }

    button.events().click([&]() {
        nana::inputbox::text entry("entry");
        nana::inputbox input_box(fm, "description", "ha");
        if (input_box.show(entry)) {
            auto value = entry.value();
            box.at(0).append(value);
        }
    });


    fm.show();
    nana::exec();
    return 0;
}