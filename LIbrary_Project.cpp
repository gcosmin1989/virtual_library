#include"LibraryApp.h"


int main()
{
    Library library;
    library.addBook({ "Barte1", "Autor1", 200, 1989, "Romance" });
    library.addBook({ "Darte2", "Autor2", 100, 2019, "Drama" });
    library.addBook({ "Aarte3", "Autor3", 300, 2020, "Thriller" });


    LibraryApp libapp(library);
    libapp.navigateMenu();

    return 0;

}

