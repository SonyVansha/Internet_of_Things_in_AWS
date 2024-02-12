#include <pgmspace.h>
#define SECRET
const char WIFI_SSID[] = "XXX";
const char WIFI_PASSWORD[] = "XXX";

#define THINGNAME "ESP8266_AWSDB"
int8_t TIME_ZONE = -5; //NYC(USA): -5 UTC
const char MQTT_HOST[] = "XXX";



// Amazon Root CA 1
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----


)KEY";

// Device Private Key
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----

-----END RSA PRIVATE KEY-----

)KEY";