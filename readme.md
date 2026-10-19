# 英雄联盟偏移与特征码数据库

面向 **26.20 / 16.20.824.8524（正式国服）** 的中文偏移记录。覆盖上游全部 735 个输入项，去重后 671 个主项；当前发布 76 个主项定位，13 个主项具有运行时语义证据。历史未确认值保留在 `previous_*`，不再冒充当前偏移。

## 文件说明

| 文件 | 内容 |
| --- | --- |
| `src/offsets.json` | 唯一偏移数据源、兼容别名及验证状态 |
| `src/offsets.hpp` | 只包含达到发布条件的常量；不含固定模块基址 |
| `src/signatures.json` | 全部原输入项的特征、前后 32 字节窗口、命中数和解析规则 |
| `src/quick_usage/all_offsets.hpp` | 动态模块基址和读取回调驱动的只读玩家快照示例 |
| `docs/验证报告.md` | 核验方式、证据等级及仍未确认的内容 |
| `archive/upstream-26xx/` | 四份上游原文文件，供历史追溯 |

## 使用方式

以 C++17 包含 `src/quick_usage/all_offsets.hpp`，提供 `bool ReadMemory(std::uintptr_t, void*, std::size_t, void*)` 回调，调用 `LeagueSnapshot::ReadLocalPlayer(module_base, callback, context, snapshot)`。回调成功必须表示已完整读取请求字节。模块基址需在当前进程中动态获取。

RVA 加当前模块基址，字段偏移加正确对象地址。`null` 项和 `previous_*` 不应参与当前内存读取。

## 核验边界

CE MCP 复读比对确认指令字节和定位；本地玩家字段另以当前游戏数据交叉验证。函数名称沿用上游并保留语义状态，未执行游戏函数，也未发布未经证实的函数原型。完整情况见[验证报告](docs/验证报告.md)。

原始来源：[LadyDarknes/League-Offsets](https://github.com/LadyDarknes/League-Offsets)。本次保留原始文件并记录纠错，不把上游的“verified”文案当作实测证据。
