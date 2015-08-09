#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE percent_coder
#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>
#include <booster/cgix/percent_coder.hpp>

BOOST_AUTO_TEST_CASE(encode_string)
{
    booster::cgix::percent_coder pc;

    {
        std::string original("Hello, \"World\"!");
        std::string actual;
        std::string expected("Hello%2C+%22World%22%21");
        pc.encode(original.begin(), original.end(),
                  std::back_inserter(actual), true);
        BOOST_CHECK_EQUAL(expected, actual);
    }
    
    {
        std::string original("Hello, \"World\"!");
        std::string actual;
        std::string expected("Hello%2C%20%22World%22%21");
        pc.encode(original.begin(), original.end(),
                  std::back_inserter(actual), false);
        BOOST_CHECK_EQUAL(expected, actual);
    }
    
}

BOOST_AUTO_TEST_CASE(encode_vector)
{
    booster::cgix::percent_coder pc;
    
    {
        std::string original("Hello, \"World\"!");
        std::vector<char> actual;
        std::vector<char> expected
        {
            'H', 'e', 'l', 'l', 'o',
            '%', '2', 'C', '+', '%', '2', '2',
            'W', 'o', 'r', 'l', 'd', '%', '2', '2',
            '%', '2', '1'
        };
        pc.encode(original.begin(), original.end(),
                  std::back_inserter(actual), true);
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
    {
        std::string original("Hello, \"World\"!");
        std::vector<char> actual;
        std::vector<char> expected
        {
            'H', 'e', 'l', 'l', 'o',
            '%', '2', 'C', '%', '2', '0', '%', '2', '2',
            'W', 'o', 'r', 'l', 'd', '%', '2', '2',
            '%', '2', '1'
        };
        pc.encode(original.begin(), original.end(),
                  std::back_inserter(actual), false);
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
}

BOOST_AUTO_TEST_CASE(encode_stream)
{
    booster::cgix::percent_coder pc;
    
    {
        std::string original("Hello, \"World\"!");
        std::ostringstream actual_stream;
        std::string expected("Hello%2C+%22World%22%21");
        pc.encode(original.begin(), original.end(),
                  std::ostream_iterator<char>(actual_stream), true);
        std::string actual = actual_stream.str();
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
    {
        std::string original("Hello, \"World\"!");
        std::ostringstream actual_stream;
        std::string expected("Hello%2C%20%22World%22%21");
        pc.encode(original.begin(), original.end(),
                  std::ostream_iterator<char>(actual_stream), false);
        std::string actual = actual_stream.str();
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
}

BOOST_AUTO_TEST_CASE(encode_string_overload)
{
    booster::cgix::percent_coder pc;
    
    {
        std::string original("Hello, \"World\"!");
        std::string actual;
        std::string expected("Hello%2C+%22World%22%21");
        actual = pc.encode(original, true);
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
    {
        std::string original("Hello, \"World\"!");
        std::string actual;
        std::string expected("Hello%2C%20%22World%22%21");
        actual = pc.encode(original, false);
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
}

// TODO: Test cases for decoding below!!! FINISH!




BOOST_AUTO_TEST_CASE(decode_string)
{
    booster::cgix::percent_coder pc;
    
    {
        std::string original("Hello%2C+%22World%22%21");
        std::string actual;
        std::string expected("Hello, \"World\"!");
        pc.decode(original.begin(), original.end(),
                  std::back_inserter(actual), true);
        BOOST_CHECK_EQUAL(expected, actual);
    }
    
    {
        std::string original("Hello%2C%20%22World%22%21");
        std::string actual;
        std::string expected("Hello, \"World\"!");
        pc.decode(original.begin(), original.end(),
                  std::back_inserter(actual), false);
        BOOST_CHECK_EQUAL(expected, actual);
    }
    
}

BOOST_AUTO_TEST_CASE(decode_vector)
{
    booster::cgix::percent_coder pc;
    
    {
        std::vector<char> original
        {
            'H', 'e', 'l', 'l', 'o',
            '%', '2', 'C', '+', '%', '2', '2',
            'W', 'o', 'r', 'l', 'd', '%', '2', '2',
            '%', '2', '1'
        };
        std::vector<char> actual;
        std::string expected("Hello, \"World\"!");
        pc.decode(original.begin(), original.end(),
                  std::back_inserter(actual), true);
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
    {
        std::vector<char> original
        {
            'H', 'e', 'l', 'l', 'o',
            '%', '2', 'C', '%', '2', '0', '%', '2', '2',
            'W', 'o', 'r', 'l', 'd', '%', '2', '2',
            '%', '2', '1'
        };
        std::vector<char> actual;
        std::string expected("Hello, \"World\"!");
        
        pc.decode(original.begin(), original.end(),
                  std::back_inserter(actual), false);
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
}

BOOST_AUTO_TEST_CASE(decode_stream)
{
    booster::cgix::percent_coder pc;
    
    {
        std::string original("Hello%2C+%22World%22%21");
        std::ostringstream actual_stream;
        std::string expected("Hello, \"World\"!");
        pc.decode(original.begin(), original.end(),
                  std::ostream_iterator<char>(actual_stream), true);
        std::string actual = actual_stream.str();
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
    {
        std::string original("Hello%2C%20%22World%22%21");
        std::ostringstream actual_stream;
        std::string expected("Hello, \"World\"!");
        pc.decode(original.begin(), original.end(),
                  std::ostream_iterator<char>(actual_stream), false);
        std::string actual = actual_stream.str();
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
}

BOOST_AUTO_TEST_CASE(decode_string_overload)
{
    booster::cgix::percent_coder pc;
    
    {
        std::string original("Hello%2C+%22World%22%21");
        std::string actual;
        std::string expected("Hello, \"World\"!");
        actual = pc.decode(original, true);
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
    {
        std::string original("Hello%2C%20%22World%22%21");
        std::string actual;
        std::string expected("Hello, \"World\"!");
        actual = pc.decode(original, false);
        BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                      actual.begin(), actual.end());
    }
    
}
