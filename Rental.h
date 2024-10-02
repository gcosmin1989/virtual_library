#pragma once
struct Rental
{
    static int increment;

    int rent_id;
    int book_id;
    int user_id;
    int rent_date;
    int return_date;

    Rental(int book_id, int user_id, int rent_date, int return_date);

};

