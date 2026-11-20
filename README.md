# Prompt Forge（Android）

> 单文件提示词工具的安卓封装版：在一个 App 里浏览 2400+ 标签、管理三套提示词体系、下载模型，并在手机上尝试本机出图。

## 这是什么

Prompt Forge 原本是一个单文件 HTML 工具（`assets/index.html`，约 1.0 MB），无需联网也无需后端，浏览器打开就能用。本仓库是它的安卓外壳，把网页装进 WebView，再通过 JS 桥接（`window.PFEngine`）把「模型下载」「模型管理」「本机出图」这些需要系统能力的事情交给原生层做。

目标是做一个**不依赖 Termux**、装完即用的本地出图 App，方向上对标 Local Dream。

## 功能

- **提示词实验台**：Anima / MOSS-Image / Krea2 三套体系可切换，中英双语提示词，可导出到其它 App。
- **标签库**：内置 2400+ 标签，按画风、人物、场景、光影等维度检索，点选即拼进提示词。
- **云端通道**：支持 OpenAI 兼容、Stability、SD WebUI 等 14 家服务商，填地址和 Key 就能出图。
- **本机通道**：模型下载（断点续传）、模型列表、加载/卸载、出图（引擎接入中）。
- **离线可用**：界面与标签库全部内置，断网也能编辑提示词。

## 当前进度

| 模块 | 状态 |
| --- | --- |
| 界面 / 标签库 / 云端通道 | ✅ 可用 |
| 模型下载与管理 | ✅ 可用 |
| sd.cpp 引擎编译与链接 | ✅ CI 自动完成 |
| 本机出图（`sd_generate_image` + 像素回传） | 🚧 接入中 |

## 怎么装

到 Releases 下载最新 `build-*` 里的 `app-debug.apk`，允许「安装未知来源应用」后直接装。

> 只支持 arm64-v8a 且 Android 8.0（minSdk 26）以上的机型。

## 怎么自己编

构建全部在 GitHub Actions 上完成，入口是 `.github/workflows/main.yml`，逻辑写在云端脚本里（`/(tmp)/b.sh`），流程是：

1. 装 Android SDK / NDK 27 / CMake 3.22
2. 拉取界面与 Kotlin 源码，补 `Theme.AppCompat.NoActionBar`
3. 拉 `leejet/stable-diffusion.cpp` 并编译成 arm64 静态库
4. 用 NDK clang 把 `jni_bridge.cpp` 与四个 `.a` 链接成 `libpfengine.so`
5. 生成 Gradle 配置，`assembleDebug`
6. 产物丢进 `out/`，附到 Release

每次构建都会把关键日志推到 `ci-report` 分支的 `ci/last.txt`，失败时看这个文件比翻 Actions 日志快。

## 目录

```
app/src/main/
├─ assets/index.html      # 单文件界面（1.0 MB）
├─ cpp/jni_bridge.cpp     # JNI 桥，暴露给 Kotlin
└─ java/com/promptforge/app/
   ├─ MainActivity.kt      # WebView 壳 + 桥注册
   ├─ PFEngineBridge.kt    # JS <-> 原生 的接口层
   ├─ EngineManager.kt     # .so 加载、模型加载、状态
   ├─ ModelRepository.kt   # 模型目录与权重文件
   └─ Downloader.kt        # 断点续传下载
```

## 技术栈

WebView + Kotlin 2.0 + AGP 8.7 + NDK 27 + stable-diffusion.cpp（GGUF 权重，CPU 推理）。

## 说明

- 本机出图在手机 CPU 上跑 SD1.5 级别模型，512×512 大约 1-5 分钟，属于「能用但不快」。
- 模型权重不随包分发，需要 App 内单独下载（约 1-2 GB）。
- 界面与标签库遵循工具自身的许可；引擎部分来自 `stable-diffusion.cpp`（MIT）。
