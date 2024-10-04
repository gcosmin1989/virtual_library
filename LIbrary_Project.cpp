


#include"LibraryApp.h"



std::string draw_message = "Discover, Explore, and Enjoy Your Next Read!";



//static void drawWelcomeMessage(std::string show_text="Discover, Explore, and Enjoy Your Next Read!") {
//
//    int total_length = 56;
//    int inner_length = total_length - 2;
//    int total_padding = inner_length - show_text.length();
//    int left_padding = total_padding / 2;
//    int right_padding = total_padding - left_padding;
//
//    std::string second_text_draw = "*"
//        + std::string(left_padding, ' ')
//        + show_text
//        + std::string(right_padding, ' ')
//        + "*";
//
//    std::string separator_draw =    "********************************************************";
//    std::string box_draw =          "*                                                      *";
//    std::string first_text_draw =   "*           WELCOME TO YOUR VIRTUAL LIBRARY!           *";
//    std::string spaces = "                    ";
//    std::cout << spaces << separator_draw << std::endl;
//    std::cout << spaces << box_draw << std::endl;
//    std::cout << spaces << first_text_draw << std::endl;
//    std::cout << spaces << box_draw << std::endl;
//    std::cout << spaces << separator_draw << std::endl;
//    std::cout << spaces << box_draw << std::endl;
//    std::cout << spaces << second_text_draw << std::endl;
//    std::cout << spaces << box_draw << std::endl;
//    std::cout << spaces << separator_draw << std::endl << std::endl;
//
//    
//}





int main()
{
    LibraryApp libapp;
    libapp.navigateMenu();

   
 
    return 0;

}

