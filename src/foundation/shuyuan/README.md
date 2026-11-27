# 枢元子系统源码骨架（foundation/shuyuan）

本目录镜像 OpenHarmony 源码树中的部件布局。五个部件骨架均已落地，结构同构；`lingtai/` 为参照样板，其余四层按相同骨架替换了 SA ID、进程名与接口。

公共错误码集中在 `interfaces/innerkits/include/shuyuan_common.h`（`SHUYUAN_OK` 及三个错误码），各层接口头经 `#include` 引用，不在层内重复定义；串通测试客户端位于 `tools/shuyuan_demo_client/`。

## 部件与 SA 分配

| 层 | 部件目录 | SA ID | 进程名 | 动态库 | SELinux 域 | 状态 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 灵台（调度中枢） | `lingtai/` | 9901 | `lingtai_service` | `liblingtai_service.z.so` | `u:r:lingtai_service:s0` | 骨架已落地 |
| 监观（感知层） | `jianguan/` | 9902 | `jianguan_service` | `libjianguan_service.z.so` | `u:r:jianguan_service:s0` | 骨架已落地 |
| 和鸣（协作机制） | `heming/` | 9903 | `heming_service` | `libheming_service.z.so` | `u:r:heming_service:s0` | 骨架已落地 |
| 令终（任务闭环） | `lingzhong/` | 9904 | `lingzhong_service` | `liblingzhong_service.z.so` | `u:r:lingzhong_service:s0` | 骨架已落地 |
| 敬止（治理） | `jingzhi/` | 9905 | `jingzhi_service` | `libjingzhi_service.z.so` | `u:r:jingzhi_service:s0` | 骨架已落地 |

## 各层接口速览

| 部件 | IPC 方法 |
| :--- | :--- |
| 灵台 9901 | `RegisterAgent` / `UnregisterAgent` / `SubmitIntent` / `GetTaskStatus` / `IsReady` / `GetBootStatus` |
| 监观 9902 | `GetSnapshot` / `IsReady` |
| 和鸣 9903 | `DispatchPlan` / `GetCollabStatus` / `IsReady` |
| 令终 9904 | `AttachTask` / `FinishTask` / `GetTaskFinalState` / `IsReady` |
| 敬止 9905 | `PreAuthorize` / `Audit` / `IsReady` |

## 复制一个新部件的步骤

1. 复制 `lingtai/` 整目录，改名为目标层拼音标识。
2. 全局替换：进程名、库名、SA ID、命名空间类名、接口描述符字符串、HiLog 标签。
3. 按 `interfaces/innerkits/include/` 中的接口草案重写业务方法（见项目根目录 `03-工程骨架规划.md` 第 4 节）。
4. 同步修改 `sa_profile/<SAID>.xml` 的 `<name>`、`<process>`、`<libpath>`。
5. 在产品配置 `subsystems` 中登记 `shuyuan` 子系统及本部件。

## 样板文件清单（以灵台为例）

```
lingtai/
├── BUILD.gn                                  # 动态库 + 接口集合目标
├── bundle.json                               # 部件登记（sub_component）
├── interfaces/innerkits/include/
│   └── i_lingtai_service.h                    # IPC 接口 + SA ID（错误码见公共头）
├── services/
│   ├── include/
│   │   ├── lingtai_service_stub.h
│   │   ├── lingtai_service_proxy.h
│   │   └── lingtai_service.h
│   ├── src/
│   │   ├── lingtai_service_stub.cpp
│   │   ├── lingtai_service_proxy.cpp
│   │   └── lingtai_service.cpp
│   └── etc/
│       ├── BUILD.gn
│       └── init/
│           ├── lingtai_service.cfg
│           └── lingtai_service.rc
└── sa_profile/
    ├── BUILD.gn
    └── 9901.xml
```

子系统级（与各部件目录平级）：

```
interfaces/innerkits/include/shuyuan_common.h   # 公共错误码 + 就绪参数名常量
init/shuyuan_boot.cfg                           # 子系统级统一启动时序（同 job 按序拉起五层）
init/BUILD.gn                                   # 统一时序 cfg 安装目标
sepolicy/                                       # SELinux 策略骨架（五域 type + service_contexts/file_contexts 草稿）
tools/shuyuan_demo_client/                      # 跨 SA 串通测试客户端
```

> 骨架中的 GN 依赖目标名、Parcel 序列化 API、系统属性写入接口等，需在真实源码树中核对（见 `07-阶段一自研手册.md` 的待核实项）。
