#include <string>
#include <stdexcept>
#include "gtest/gtest.h"
using namespace std;

#include "Sedan.h"

static const double SedanPricePerKm = 0.29;

static void CheckSedanProperties(Sedan* sedanPtr, string manufacturer, string model, int buildYear,
                                 string licencePlate, int kilometers, bool isAvailable, bool hasTowbar)
{
    EXPECT_EQ(manufacturer, sedanPtr->GetManufacturer());
    EXPECT_EQ(model, sedanPtr->GetModel());
    EXPECT_EQ(buildYear, sedanPtr->GetBuildYear());
    EXPECT_EQ(licencePlate, sedanPtr->GetLicencePlate());
    EXPECT_EQ(kilometers, sedanPtr->GetKilometers());
    EXPECT_EQ(isAvailable, sedanPtr->IsAvailable());
    EXPECT_EQ(hasTowbar, sedanPtr->HasTowBar());
}

TEST(SedanIllegalParameterTests, test_construction_exception)
{
    EXPECT_THROW(new Sedan("Ford", "Ka", 1889, "licenceplate", true), invalid_argument);
    EXPECT_NO_THROW(new Sedan("Ford", "Ka", 1890, "licenceplate", true));
}

class SedanTest : public ::testing::Test
{
    protected:
        SedanTest()
        {
            testPtr = new Sedan("Audi", "R8", 2015, "1-c++-98", false);
        }
        
        Sedan* testPtr;
};

TEST_F(SedanTest, test_construction_values_copied_correctly)
{
    CheckSedanProperties(testPtr, "Audi", "R8", 2015, "1-c++-98", 0, true, false);
}

TEST_F(SedanTest, test_car_rent_when_available)
{
    EXPECT_TRUE(testPtr->Rent());
}

TEST_F(SedanTest, test_car_rent_when_unavailable)
{
    EXPECT_TRUE(testPtr->Rent());
    EXPECT_FALSE(testPtr->Rent());
}

TEST_F(SedanTest, test_car_return_when_not_rented)
{
    EXPECT_THROW(testPtr->Return(20), logic_error);
}

TEST_F(SedanTest, test_car_return_when_rented_with_km_ok_and_km_too_low)
{
    EXPECT_TRUE(testPtr->Rent());
    EXPECT_EQ(SedanPricePerKm * 20, testPtr->Return(20));

    EXPECT_TRUE(testPtr->Rent());
    EXPECT_THROW(testPtr->Return(19), invalid_argument);    
    EXPECT_EQ(0, testPtr->Return(20));
}

TEST_F(SedanTest, test_car_needsCleaning_after_construction)
{
    EXPECT_FALSE(testPtr->NeedsCleaning());
}

TEST_F(SedanTest, test_car_needsCleaning)
{
    EXPECT_TRUE(testPtr->Rent());
    EXPECT_EQ(SedanPricePerKm * 999, testPtr->Return(999));
    EXPECT_FALSE(testPtr->NeedsCleaning());

    EXPECT_TRUE(testPtr->Rent());
    EXPECT_EQ(SedanPricePerKm * 1, testPtr->Return(1000));
    EXPECT_TRUE(testPtr->NeedsCleaning());
}

TEST_F(SedanTest, test_clean_car_that_is_not_dirty)
{
    testPtr->Clean();
    EXPECT_FALSE(testPtr->NeedsCleaning());
}

TEST_F(SedanTest, test_clean_car)
{
    EXPECT_TRUE(testPtr->Rent());
    EXPECT_EQ(SedanPricePerKm * 1000, testPtr->Return(1000));
    EXPECT_TRUE(testPtr->NeedsCleaning());

    testPtr->Clean();
    EXPECT_FALSE(testPtr->NeedsCleaning());
}

TEST_F(SedanTest, test_toString)
{
    // before the stringstream change:
    EXPECT_EQ("Audi - R8, 1-c++-98", testPtr->ToString());
    // after the stringstream change:
    //EXPECT_EQ("Audi - R8 (2015), 1-c++-98, 0 km", testPtr->ToString());
}

