//
// Created by samuaz on 3/10/21.
//

#include <gtest/gtest.h>
#include <wintercpp/winter.h>

#include <optional>
#include <string>

#include "wintercpp/exception/generic/winter_exception.h"

struct Person {
  Person(std::string name) : name_(name) {}
  std::string name_;
};

TEST(winterResponse, thenOnError) {
  auto response = winter::data::Response<int>::Error("not found");

  auto result = response.Then<int>([]() -> int { return 0; }, []() -> int { return 1; });

  EXPECT_EQ(result, 1);
}

TEST(winterResponse, thenOnSuccess) {
  auto response = winter::data::Response<int>::Success(1);

  auto result = response.Then<int>([&]() -> int { return 0; }, [&]() -> int { return 1; });

  EXPECT_EQ(result, 0);
}

TEST(winterResponse, thenWithVoid) {
  auto response = winter::data::Response<int>::Success(1);

  int value = 0;

  response.Then<void>([&]() -> void { value = value + 1; }, [&]() -> void { value = value + 2; });

  EXPECT_EQ(value, 1);
}

TEST(winterResponse, thenWithResponse) {
  auto response = winter::data::Response<int>::Success(1);

  auto value = response.Then<int>([&](const winter::data::Response<int> &value) -> int { return value.Value() + 1; }, [&](const winter::data::Response<int> &value) -> int { return value.Value() + 2; });

  EXPECT_EQ(value, 2);
}

TEST(winterResponse, thenExecute) {
  auto response = winter::data::Response<int>::Success(1);

  auto value = response.Then<int>([&](const winter::data::Response<int> &value) -> int { return value.Value() + 1; });

  EXPECT_EQ(value, 2);
}

TEST(winterResponse, thenExecuteVoid) {
  auto response = winter::data::Response<int>::Success(1);

  auto value = response.Then<int>([&]() -> int { return 2; });

  EXPECT_EQ(value, 2);
}

TEST(winterResponse, onSuccess) {
  auto response = winter::data::Response<int>::Success(1);

  auto value = response.OnSuccess<int>(
      [&](const winter::data::Response<int> &value) -> int { return value.Value() + 1; });

  EXPECT_EQ(value, 2);
}

TEST(winterResponse, onSuccessVoid) {
  auto response = winter::data::Response<int>::Success(1);

  auto value = response.OnSuccess<int>([&]() -> int { return 2; });

  EXPECT_EQ(value, 2);
}

TEST(winterResponse, onSuccessSameResponseTrue) {
  auto response = winter::data::Response<int>::Success(1);

  auto value = response.OnSuccess<winter::data::Response<int>>(
      [&](const winter::data::Response<int> &value) -> winter::data::Response<int> {
        return winter::data::Response<int>::Success(value.Value() + 1);
      });

  EXPECT_EQ(value->Value(), 2);
}

TEST(winterResponse, onSuccessSameResponseFalse) {
  auto response = winter::data::Response<int>::Error("not found");

  auto value = response.OnSuccess<winter::data::Response<int>>(
      [&](const winter::data::Response<int> &value) -> winter::data::Response<int> {
        return winter::data::Response<int>::Success(value.Value() + 1);
      });

  EXPECT_EQ(value, std::nullopt);
}

TEST(winterResponse, onError) {
  auto response = winter::data::Response<int>::Error("not found");

  auto value = response.OnError<int>([&]() -> int { return 1; });

  EXPECT_EQ(value, 1);
}

TEST(winterResponse, onErrorSameResponse) {
  auto response = winter::data::Response<int>::Error("not found");

  auto value = response.OnError<int>([&](const winter::data::Response<int> &) -> int { return 1; });

  EXPECT_EQ(value, 1);
}

TEST(winterResponse, returnOrThrowShouldReturn) {
  auto response = winter::data::Response<int>::Success(1);

  auto value = response.ReturnOrThrow();

  EXPECT_EQ(value, 1);
}

TEST(winterResponse, returnOrThrowShouldThrow) {
  auto response = winter::data::Response<int>::Error("not found");
  EXPECT_THROW(response.ReturnOrThrow(), winter::WinterException);
}

TEST(winterResponse, testHasValuePointerThrow) {
  auto response = winter::data::Response<int *>::Error("not found");
  EXPECT_THROW(response.ReturnOrThrow(), winter::WinterException);
}

TEST(winterResponse, testHasValuePointer) {
  auto response = winter::data::Response<int *>::Success(new int(5));
  int *value = response.ReturnOrThrow();
  EXPECT_EQ(*value, 5);
  delete value;
}

TEST(winterResponse, testHasSharedPtr) {
  auto response = winter::data::Response<std::shared_ptr<int>>::Success(std::make_shared<int>(5));
  int *value = response.ReturnOrThrow().get();
  EXPECT_EQ(*value, 5);
}

TEST(winterResponse, testHasValuePointerWithStruct) {
  auto response = winter::data::Response<Person *>::Success(new Person("samuel"));
  Person *value = response.ReturnOrThrow();
  EXPECT_EQ(value->name_, "samuel");
  delete value;
}

TEST(winterResponse, testHasValueWithStruct) {
  auto response = winter::data::Response<Person>::Success(Person("samuel"));
  Person value = response.ReturnOrThrow();
  EXPECT_EQ(value.name_, "samuel");
}