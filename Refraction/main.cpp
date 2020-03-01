#include "frist-sample/include/json-reader/JsonReader.h"
#include <string>

int main() 
{
    Json::Value invoices;
    std::string invoicesPath = "frist-sample\\data\\invoices.json";
    jsonReader(invoicesPath, invoices);
    printInvoices(invoices);

    Json::Value plays;
    std::string playsPath = "frist-sample\\data\\plays.json";
    jsonReader(playsPath, plays);
    printPlays(plays);
    return 0;
}