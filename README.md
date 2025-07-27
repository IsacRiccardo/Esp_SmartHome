# Esp_SmartHome

This project is an ESP32-based Smart Home implementation using the ESP-IDF framework. It provides WiFi connectivity and HTTP communication capabilities for home automation purposes.

## Features

- WiFi connectivity management
- HTTP client/server functionality
- ESP32 microcontroller support
- Non-OTA partition scheme

## Project Structure

```
├── include/          # Header files
├── lib/             # External libraries
│   ├── Http/        # HTTP implementation
│   └── WiFi/        # WiFi management
├── src/             # Main application source
└── test/            # Test files
```

## Prerequisites

- PlatformIO IDE
- ESP32 development board
- ESP-IDF framework

## Building and Flashing

1. Clone this repository:
   ```
   git clone https://github.com/IsacRiccardo/Esp_SmartHome.git
   ```

2. Open the project in PlatformIO IDE

3. Build the project:
   ```
   pio run
   ```

4. Upload to your ESP32:
   ```
   pio run --target upload
   ```

## Configuration

The project uses the following configuration files:
- `platformio.ini` - PlatformIO configuration
- `CMakeLists.txt` - CMake build system configuration
- `sdkconfig.esp32dev` - ESP32 SDK configuration
- `partitions_no_ota.csv` - Custom partition table without OTA support

## Libraries

### WiFi Library
Located in `lib/WiFi`, handles WiFi connection and management.

### HTTP Library
Located in `lib/Http`, provides HTTP communication capabilities.

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

N/A

## Author

IsacRiccardo