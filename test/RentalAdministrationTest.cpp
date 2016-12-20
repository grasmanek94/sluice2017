#include <string>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "RentalAdministration.h"

using ::testing::Return;

TEST(RentalAdministrationAdd, test_add_car_to_empty_administration)
{
    RentalAdministration admin;
    Car car;
    EXPECT_CALL(car, GetLicencePlate()).WillOnce(Return("fh-01-ict"));
    EXPECT_TRUE(admin.Add(&car));
}

TEST(RentalAdministrationAdd, test_add_car_to_existing_administration)
{
    RentalAdministration admin;
    Car car;
    EXPECT_CALL(car, GetLicencePlate()).WillOnce(Return("fh-01-ict"));
    EXPECT_TRUE(admin.Add(&car));

    EXPECT_CALL(car, GetLicencePlate()).WillOnce(Return("fh-02-ict")).WillOnce(Return("fh-01-ict"));
    EXPECT_TRUE(admin.Add(&car));
}

TEST(RentalAdministrationAdd, test_add_existing_car_to_administration)
{
    RentalAdministration admin;
    Car car;
    EXPECT_CALL(car, GetLicencePlate()).WillOnce(Return("fh-01-ict"));
    EXPECT_TRUE(admin.Add(&car));

    EXPECT_CALL(car, GetLicencePlate()).WillOnce(Return("fh-01-ict")).WillOnce(Return("fh-01-ict"));
    EXPECT_FALSE(admin.Add(&car));
}

TEST(RentalEmptyAdministration, test_rent_car_in_empty_administration)
{
    RentalAdministration admin;
    EXPECT_THROW(admin.RentCar("0987"), out_of_range);
}

TEST(RentalEmptyAdministration, test_return_car_in_empty_administration)
{
    RentalAdministration admin;
    EXPECT_THROW(admin.ReturnCar("6543", 12), out_of_range);
}

TEST(RentalEmptyAdministration, test_clean_car_in_empty_administration)
{
    RentalAdministration admin;
    EXPECT_THROW(admin.CleanCar("6543"), out_of_range);
}

TEST(RentalEmptyAdministration, test_get_car_in_empty_administration)
{
    RentalAdministration admin;
    EXPECT_EQ(0, admin.GetCars().size());
}

class AdminTest : public ::testing::Test
{
    protected:
        AdminTest()
        {
            licencePlates[0] = "abcd";
            licencePlates[1] = "efgh";
            // Add car with licencePlate "abcd" and car with licencePlate "efgh"
            EXPECT_CALL(car, GetLicencePlate()).WillOnce(Return(licencePlates[0])) // first add
                                               .WillOnce(Return(licencePlates[1])) // second value to add
                                               .WillOnce(Return(licencePlates[0])); // to check if second value already exist
            EXPECT_TRUE(admin.Add(&car));
            EXPECT_TRUE(admin.Add(&car));
            EXPECT_EQ(2, admin.GetCars().size());
        }
        
        RentalAdministration admin;
        Car car;
        string licencePlates[2];
};

TEST_F(AdminTest, test_rent_non_existing_car)
{
    EXPECT_CALL(car, GetLicencePlate()).WillRepeatedly(Return("aa-11-bb"));
    EXPECT_THROW(admin.RentCar(licencePlates[0]), out_of_range);
}

TEST_F(AdminTest, test_rent_existing_car)
{
    EXPECT_CALL(car, GetLicencePlate()).WillOnce(Return(licencePlates[0]));
    EXPECT_CALL(car, Rent()).WillOnce(Return(true));
    EXPECT_EQ(true, admin.RentCar(licencePlates[0]));
}

TEST_F(AdminTest, test_rent_existing_but_already_rented_car)
{
    EXPECT_CALL(car, GetLicencePlate()).WillOnce(Return(licencePlates[0]));
    EXPECT_CALL(car, Rent()).WillOnce(Return(false));
    EXPECT_EQ(false, admin.RentCar(licencePlates[0]));
}

TEST_F(AdminTest, test_return_non_existng_car)
{
    EXPECT_CALL(car, GetLicencePlate()).WillRepeatedly(Return("aa-11-bb"));
    EXPECT_THROW(admin.ReturnCar(licencePlates[0], 12), out_of_range);
}

TEST_F(AdminTest, test_return_existng_car)
{
    EXPECT_CALL(car, GetLicencePlate()).WillOnce(Return(licencePlates[0]));
    EXPECT_CALL(car, Return(12)).WillOnce(Return(100));
    EXPECT_EQ(100, admin.ReturnCar(licencePlates[0], 12));
}

TEST_F(AdminTest, test_clean_non_existing_car)
{
    EXPECT_CALL(car, GetLicencePlate()).WillRepeatedly(Return("aa-11-bb"));
    EXPECT_THROW(admin.CleanCar(licencePlates[0]), out_of_range);
}

TEST_F(AdminTest, test_clean_existing_car)
{
    EXPECT_CALL(car, GetLicencePlate()).WillOnce(Return(licencePlates[0]));
    EXPECT_CALL(car, Clean()).Times(1);
    EXPECT_NO_THROW(admin.CleanCar(licencePlates[0]));
}

