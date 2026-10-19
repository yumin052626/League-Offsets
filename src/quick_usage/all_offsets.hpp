#pragma once
#include <cstddef>
#include <cstdint>
#include "../offsets.hpp"

// 只读示例：读取实现由调用者提供，不包含游戏函数调用、写内存或固定基址。
namespace LeagueSnapshot {
struct Vec3 { float x, y, z; };
struct PlayerSnapshot {
    std::uintptr_t address{};
    float health{}, max_health{}, mana{}, max_mana{};
    Vec3 position{};
    std::uint32_t network_id{};
    std::uint16_t index{};
};
using ReadMemory = bool (*)(std::uintptr_t address, void* destination, std::size_t size, void* context);

inline bool ReadLocalPlayer(std::uintptr_t module_base, ReadMemory read, void* context, PlayerSnapshot& result) {
    if (!module_base || !read) return false;
    PlayerSnapshot snapshot{};
    if (!read(module_base + Offsets::Globals::LocalPlayer, &snapshot.address, sizeof(snapshot.address), context) || !snapshot.address) return false;
    if (!read(snapshot.address + Offsets::Standard::GameObject::oHealth, &snapshot.health, sizeof(snapshot.health), context)) return false;
    if (!read(snapshot.address + Offsets::Standard::GameObject::oMaxHealth, &snapshot.max_health, sizeof(snapshot.max_health), context)) return false;
    if (!read(snapshot.address + Offsets::Standard::GameObject::oMana, &snapshot.mana, sizeof(snapshot.mana), context)) return false;
    if (!read(snapshot.address + Offsets::Standard::GameObject::oMaxMana, &snapshot.max_mana, sizeof(snapshot.max_mana), context)) return false;
    if (!read(snapshot.address + Offsets::Standard::GameObject::oPosition, &snapshot.position, sizeof(snapshot.position), context)) return false;
    if (!read(snapshot.address + Offsets::Standard::GameObject::oNetworkID, &snapshot.network_id, sizeof(snapshot.network_id), context)) return false;
    if (!read(snapshot.address + Offsets::Standard::GameObject::oIndex, &snapshot.index, sizeof(snapshot.index), context)) return false;
    result = snapshot;
    return true;
}
} // 命名空间 LeagueSnapshot
