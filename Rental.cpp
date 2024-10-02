#include "Rental.h"

int Rental::increment = 200;


Rental::Rental(int book_id, int user_id, int rent_date, int return_date)
    : book_id(book_id), user_id(user_id), rent_date(rent_date), return_date(return_date) {
    increment++;
    rent_id = increment;
}
