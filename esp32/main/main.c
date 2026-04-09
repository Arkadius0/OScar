#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "esp_log.h"

static const char *TAG = "SPI_MASTER";

// Defiene SPI pins
#define PIN_NUM_MISO 19
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  18
#define PIN_NUM_CS   5

spi_device_handle_t spi_handle;

void spi_master_init()
{
    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096
    };

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1 * 1000 * 1000, // Clock out at 1 MHz
        .mode = 0,                            // SPI mode 0
    };

    esp_err_t ret = spi_bus_initialize(SPI2_HOST, &buscfg, 1);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize SPI bus");
        return;
    }

    ret = spi_bus_add_device(SPI2_HOST, &devcfg, &spi_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to add SPI device");
        return;
    }
}

void spi_master_transmit(const uint8_t *data, size_t length)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t)); // Zero out the transaction
    t.length = length * 8;    // Length in bits
    t.tx_buffer = data;      // Data to send

    esp_err_t ret = spi_device_transmit(spi_handle, &t);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to transmit SPI data");
    }
}

void app_main(void)
{
    spi_master_init();

    uint8_t data_to_send[] = {0x01}; // Data
    while (1) {
        spi_master_transmit(data_to_send, sizeof(data_to_send));
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Transmit every 1 second
    }
}
