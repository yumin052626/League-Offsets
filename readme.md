# 英雄联盟偏移与特征码数据库

面向 **26.20 / 16.20.824.8524（正式国服）** 的中文偏移记录。覆盖上游全部 735 个输入项，去重后 671 个主项；当前发布 75 个主项定位，16 个主项具有运行时语义证据。历史未确认值保留在 `previous_*`，不再冒充当前偏移。

## 文件说明

| 文件 | 内容 |
| --- | --- |
| `src/offsets.json` | 唯一偏移数据源、兼容别名及验证状态 |
| `src/offsets.hpp` | 只包含达到发布条件的常量；不含固定模块基址 |
| `src/signatures.json` | 全部原输入项的特征、前后 32 字节窗口、命中数和解析规则 |
| `src/quick_usage/all_offsets.hpp` | 动态模块基址和读取回调驱动的只读玩家快照示例 |
| `docs/验证报告.md` | 核验方式、证据等级及仍未确认的内容 |
| `docs/ce-evidence.json` | CE 复读、13 个字段快照、API 交叉和构建检查的精简证据 |
| `archive/upstream-26xx/` | 四份上游原文文件，供历史追溯 |

## 使用方式

以 C++17 包含 `src/quick_usage/all_offsets.hpp`，提供 `bool ReadMemory(std::uintptr_t, void*, std::size_t, void*)` 回调，调用 `LeagueSnapshot::ReadLocalPlayer(module_base, callback, context, snapshot)`。回调成功必须表示已完整读取请求字节。模块基址需在当前进程中动态获取。

RVA 加当前模块基址，字段偏移加正确对象地址。`null` 项和 `previous_*` 不应参与当前内存读取。

## 核验边界

CE MCP 复读比对确认指令字节和定位。3 个全局与 13 个本地玩家字段具有本局快照交叉证据；索引、网络编号和位置仅为初步语义且未做动态实验。其他全局和全部函数名称沿用上游，仅为定位候选，业务功能未确认。`fieldOfView` 内部匹配点已从函数常量中排除。完整情况见[验证报告](docs/验证报告.md)。

验证日期：2026-10-19（Asia/Shanghai）。上游提交：`817879782e6b783a6403f780d7c669e0c7bcd3de`。JSON schema 2 允许空地址并将重复名称迁移到 `aliases`；旧读取程序需要适配，不能把历史值作为当前地址。

原始来源：[LadyDarknes/League-Offsets](https://github.com/LadyDarknes/League-Offsets)。本次保留原始文件并记录纠错，不把上游的“verified”文案当作实测证据。
