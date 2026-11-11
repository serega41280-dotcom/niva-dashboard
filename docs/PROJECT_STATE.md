# Состояние проекта: Niva Dashboard (цифровая приборная панель)

Обновлено: 2026-11-04, коммит 5f8576b.

## Назначение документа
Единый источник правды о состоянии проекта. Любой ИИ-ассистент (Qwen, Cline+Ollama, ChatGPT)
в начале сессии ОБЯЗАН прочитать этот файл и не противоречить зафиксированным здесь решениям.
Обновляется после каждого milestones-шага и коммитится в репозиторий niva-dashboard.

## Оборудование
- Плата: Olimex ESP32-P4-PC (ESP32-P4NRW32: 2x400 MHz RISC-V, 768KB SRAM, 32MB PSRAM, 16MB flash).
  Плата заказана, в пути - физически ещё НЕ получена.
- Wi-Fi и Bluetooth НЕТ.
- Видео: встроенный мост LT8912B (MIPI-DSI -> HDMI), только видео; HDMI и внешний MIPI-DSI делят линии DSI.
- Пределы HDMI: до 1920x1080@30Hz или 1280x800@60Hz.
- Экран: матрица BOE NV126B5M-N42, 1920x515@60Hz (eDP), через конвертер LH-W25B-BV6 (HDMI->eDP).
  Экран проверен: работает от HDMI компьютера.
- Цель: кастомный HDMI-режим 1920x515@60Hz, пиксель-клок ~70.6 MHz по даташиту матрицы.
- Звук: кодек ES8311, разъём 3.5mm jack (HDMI звук не передаёт).

## Репозитории и роли
- niva-dashboard (этот репозиторий) - единственное место работы и коммитов.
- ESP32-P4-PC (форк и клон D:\Projects\ESP32-P4-PC) - библиотека только для чтения;
  push отключён (push-url = PUSH_DISABLED).
- D:\Projects\recipe_1440x900_hdmi.patch - справочный пример добавления кастомного HDMI-режима (4 файла).

## Программное окружение
- ESP-IDF v5.5.5, target esp32p4; графика - LVGL (managed component lvgl__lvgl).
- Эталон: p4_board_demo (Olimex), локально D:\Projects\ESP32-P4-PC\SOFTWARE\ESP-IDF\p4_board_demo;
  его HDMI по умолчанию 1280x720@60Hz.
- p4_board_demo собран из исходников успешно (app 0x1262f0 bytes, 71% partition free).

## Журнал решений
- 2026-10-11: коммит f81084c в форке добавил BSP_HDMI_RES_1920x515 в display.h копии BSP
  п4_production_test (только enum, без таймингов) - сессия ChatGPT.
- 2026-11-04: Cline (локальный) самовольно добавил 1440x900@60Hz в p4_board_demo (4 файла, без коммита);
  правки откатаны git restore, сохранены как recipe_1440x900_hdmi.patch.
- 2026-11-04: форк заморожен (PUSH_DISABLED); у Cline отключено авто-одобрение Edit;
  границы репозиториев зафиксированы в .clinerules (коммит 4eca3f1).
- 2026-11-04: components/esp-bsp скопирован из p4_board_demo в niva-dashboard; корневой CMakeLists.txt получил EXTRA_COMPONENT_DIRS; idf.py build зелёный (коммит cdf0238).
- 2026-11-04: реализован кастомный HDMI-режим 1920x515@60Hz в vendored BSP (4 файла: display.h enum, Kconfig BSP_LCD_HDMI_1920x515_60HZ, esp_lcd_lt8912b.h макросы, esp32_p4_function_ev_board.c массивы+switch+#elif); тайминги из даташита NV126B5M-N42 (pclk 70 MHz целочисл., hfp/hs/hbp=48/32/80, vfp/vs/vbp=5/5/40, htotal 2080, vtotal 565); idf.py build зелёный; коммит 5f8576b.

## Открытые вопросы
- Реализованы ли где-то в форке тайминги 1920x515 (найден только enum в p4_production_test)?
- Примет ли LH-W25B-BV6 кастомный режим 1920x515@60Hz или нужен скейлер - проверить на живом железе.
- Уточнить точные параметры hsync/vsync матрицы NV126B5M-N42 из даташита.
- sdkconfig проекта пока учебный (flash 2MB, single-app): перед прошивкой живой платы согласовать перевод на 16MB flash / 32MB PSRAM / таблицу разделов платы через sdkconfig.defaults.

## Следующие шаги
1. По приезде платы: прошить binary/ESP32-P4-PC-board-demo.bin по адресу 0x0, проверить HDMI на нашем экране.
2. Согласовать sdkconfig под плату (16MB flash, 32MB PSRAM, partitions) и зафиксировать в sdkconfig.defaults.
3. Включить режим 1920x515 через menuconfig (BSP_LCD_HDMI_EXPERIMENTAL_MODES + BSP_LCD_HDMI_1920x515_60HZ) и проверить на живом экране.
4. LVGL: макет интерфейса приборной панели.

## Правила работы с этим файлом
- В начале сессии - читать первым.
- После milestone - дополнять "Журнал решений" и обновлять "Следующие шаги".
- Записи журнала НЕ удалять, только добавлять.
- Коммит обновления: docs: update project state.