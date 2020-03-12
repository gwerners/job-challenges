#include "invert.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <memory>

using ::testing::_;
using ::testing::Return;

const char* in_str =
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod "
  "tempor incididunt ut labore et dolore magna aliqua.";
const char* in_inverted =
  ".auqila angam erolod te erobal tu tnudidicni ropmet domsuie od des ,tile "
  "gnicsipida rutetcesnoc ,tema tis rolod muspi meroL";

int
local_strcmp(const char* s1, const char* s2)
{
    IFDBG
    {
        // se as duas estao nulas, entao sao iguais...
        printf("s1[%s] s2[%s]\n",
               (s1) ? (!(*s1) ? "empty" : s1) : "NULL",
               (s2) ? (!(*s2) ? "empty" : s2) : "NULL");
    }
    if (!s1 && !s2) {
        IFDBG printf("both null\n");
        return 0;
    }
    if (!s1) {
        IFDBG printf("s1 is null\n");
        return -1;
    }
    if (!s2) {
        IFDBG printf("s2 is null\n");
        return 1;
    }
    // se as duas estao vazias, entao sao iguais...
    if (!*s1 && !*s2) {
        IFDBG printf("both empty\n");
        return 0;
    }
    IFDBG printf("normal compare\n");
    return strcmp(s1, s2);
}
class CStringData
{
  public:
    virtual char* get() = 0;
};
class CStringDataMock : public CStringData
{
  public:
    MOCK_METHOD(char*, get, ());
};

template<class T>
class TestInvert
{
  public:
    TestInvert()
      : m_initialized(false)
    {}
    bool run()
    {
        if (m_initialized) {
            IFDBG std::cout << "in " << m_in->get() << std::endl;
            invertString(m_in->get());
            IFDBG std::cout << "out " << m_in->get() << std::endl;
            if (local_strcmp(m_in->get(), m_expected->get()) == 0) {
                IFDBG
                {
                    std::cout << m_in->get() << std::endl;
                    std::cout << m_expected->get() << std::endl;
                }
                return true;
            } else {
                return false;
            }
        } else {
            if (local_strcmp(nullptr, nullptr) == 0) {
                IFDBG std::cout << "null value check ok" << std::endl;
                return true;
            } else {
                return false;
            }
        }
    }
    void setIn(std::shared_ptr<T> in)
    {
        this->m_in = in;
        m_initialized = true;
    }
    void setExpected(std::shared_ptr<T> expected)
    {
        this->m_expected = expected;
    }

  private:
    bool m_initialized;
    std::shared_ptr<T> m_in;
    std::shared_ptr<T> m_expected;
};

TEST(StringInvertTest, NormalValues)
{
    TestInvert<CStringDataMock> tst;
    std::shared_ptr<CStringDataMock> in = std::make_shared<CStringDataMock>();
    std::shared_ptr<CStringDataMock> expected =
      std::make_shared<CStringDataMock>();

    tst.setIn(in);
    tst.setExpected(expected);

    char in_buffer[125];
    char in_expected_buffer[125];
    strcpy(&in_buffer[0], in_str);
    strcpy(&in_expected_buffer[0], in_inverted);
    IFDBG
    {
        EXPECT_CALL(*in, get()).Times(5).WillRepeatedly(Return(in_buffer));
        EXPECT_CALL(*expected, get())
          .Times(2)
          .WillRepeatedly(Return(in_expected_buffer));
    }
    else
    {
        EXPECT_CALL(*in, get()).Times(2).WillRepeatedly(Return(in_buffer));
        EXPECT_CALL(*expected, get())
          .Times(1)
          .WillOnce(Return(in_expected_buffer));
    }
    EXPECT_EQ(true, tst.run());
}

TEST(StringInvertTest, EmptyValues)
{
    TestInvert<CStringDataMock> tst;
    std::shared_ptr<CStringDataMock> in = std::make_shared<CStringDataMock>();
    std::shared_ptr<CStringDataMock> expected =
      std::make_shared<CStringDataMock>();

    tst.setIn(in);
    tst.setExpected(expected);

    char in_buffer[125];
    char in_expected_buffer[125];
    in_buffer[0] = '\0';
    in_buffer[1] = '\0';
    in_expected_buffer[0] = '\0';
    in_expected_buffer[1] = '\0';
    IFDBG
    {
        EXPECT_CALL(*in, get()).Times(5).WillRepeatedly(Return(in_buffer));
        EXPECT_CALL(*expected, get())
          .Times(2)
          .WillRepeatedly(Return(in_expected_buffer));
    }
    else
    {
        EXPECT_CALL(*in, get()).Times(2).WillRepeatedly(Return(in_buffer));
        EXPECT_CALL(*expected, get())
          .Times(1)
          .WillOnce(Return(in_expected_buffer));
    }
    EXPECT_EQ(true, tst.run());
}

TEST(StringInvertTest, NullStrings)
{
    TestInvert<CStringDataMock> tst;
    std::shared_ptr<CStringDataMock> in = std::make_shared<CStringDataMock>();
    std::shared_ptr<CStringDataMock> expected =
      std::make_shared<CStringDataMock>();

    tst.setIn(in);
    tst.setExpected(expected);

    IFDBG
    {
        EXPECT_CALL(*in, get()).Times(5).WillRepeatedly(Return(nullptr));
        EXPECT_CALL(*expected, get()).Times(2).WillRepeatedly(Return(nullptr));
    }
    else
    {
        EXPECT_CALL(*in, get()).Times(2).WillRepeatedly(Return(nullptr));
        EXPECT_CALL(*expected, get()).Times(1).WillOnce(Return(nullptr));
    }
    EXPECT_EQ(true, tst.run());
}

int
main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
