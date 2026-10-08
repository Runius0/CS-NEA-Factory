import std.mem;

bitfield specialFlags {
    padding : 3;
    rounded : 1;
    type : 2;
    size : 2;
};
enum Tile : u8 {
    empty,
floor,
rock
};

enum Direction : u8 {
    up,
    right,
    down,
left
};

struct Landmark {
    u8 x;
u8 y;
specialFlags type;
};

struct Exit {
    Direction direction;
    u8 offset;
};

struct Room {
u8 width;
u8 height;
u8 entrance_x;
Tile Tiles [width * height];
Landmark specials[while(std::mem::read_unsigned($, 3) != 0x000000)];
    Exit exits[while(std::mem::read_unsigned($, 3) != 0x000000)];
};

Room roomObj @ 0x00;