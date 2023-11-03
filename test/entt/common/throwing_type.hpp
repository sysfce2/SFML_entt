#ifndef ENTT_COMMON_THROWING_TYPE_HPP
#define ENTT_COMMON_THROWING_TYPE_HPP

namespace test {

class throwing_type {
    struct test_exception {};

public:
    using exception_type = test_exception;

    static constexpr auto moved_from_value = -1;
    static constexpr auto trigger_on_value = 42;

    throwing_type(int value)
        : data{value} {}

    throwing_type(const throwing_type &other)
        : data{other.data} {
        if(data == trigger_on_value) {
            data = moved_from_value;
            throw exception_type{};
        }
    }

    throwing_type &operator=(const throwing_type &other) {
        if(other.data == trigger_on_value) {
            data = moved_from_value;
            throw exception_type{};
        }

        data = other.data;
        return *this;
    }

    int get() const {
        return data;
    }

    void set(int value) {
        data = value;
    }

private:
    int data{};
};

inline bool operator==(const throwing_type &lhs, const throwing_type &rhs) {
    return lhs.get() == rhs.get();
}

} // namespace test

#endif
