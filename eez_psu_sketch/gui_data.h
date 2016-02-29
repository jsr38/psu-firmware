#pragma once

namespace eez {
namespace psu {
namespace gui {
namespace data {

enum Unit {
    UNIT_NONE,
    UNIT_VOLT,
    UNIT_AMPER
};

union Value {
public:
    Value() {
        memset(this, 0, sizeof(Value));
    }

    Value(int value) : int_(value) {
    }
    
    Value(float value, Unit unit) {
        float_ = value;
        unit_ = unit;
    }

    bool operator ==(Value other) {
        return memcmp(this, &other, sizeof(Value)) == 0;
    }

    bool operator !=(Value other) {
        return memcmp(this, &other, sizeof(Value)) != 0;
    }

    uint8_t getInt() { return int_; }

    void toText(char *text);

private:
    int int_;
    struct {
        float float_;
        uint8_t unit_;
    };
};

int count(uint16_t id);
void select(uint16_t id, int index);
Value get(uint16_t id, bool &changed);

}
}
}
} // namespace eez::psu::ui