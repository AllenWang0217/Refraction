#include "gtest/gtest.h"
#include "../../frist-sample/include/json-reader/JsonReader.h"
#include "../../frist-sample/include/statement/statement.h"
#include <string>

struct TestStatement : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        Json::Value invoices;
        std::string invoicesPath = "frist-sample\\data\\invoices.json";
        jsonReader(invoicesPath, invoices);
        //printInvoices(invoices);

        Json::Value plays;
        std::string playsPath = "frist-sample\\data\\plays.json";
        jsonReader(playsPath, plays);
        //printPlays(plays);

        bill = statement(invoices, plays);
        printBill(bill);
    }
    Bill bill;
};

TEST_F(TestStatement, case1)
{
    ASSERT_TRUE(bill.customer == "BigCo");
    ASSERT_TRUE(bill.plays.size() == 3);
    ASSERT_TRUE(bill.plays[0].name == "Hamlet");
    ASSERT_TRUE(bill.plays[0].cost == 650);
    ASSERT_TRUE(bill.plays[0].seats == 55);
    ASSERT_TRUE(bill.plays[1].name == "As You Like It");
    ASSERT_TRUE(bill.plays[1].cost == 580);
    ASSERT_TRUE(bill.plays[1].seats == 35);
    ASSERT_TRUE(bill.plays[2].name == "Othello");
    ASSERT_TRUE(bill.plays[2].cost == 500);
    ASSERT_TRUE(bill.plays[2].seats == 40);
    ASSERT_TRUE(bill.total == 1730);
    ASSERT_TRUE(bill.credit == 47);
}
