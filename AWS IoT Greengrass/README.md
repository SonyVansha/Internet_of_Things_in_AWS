# Greengrass devices

## 1. Buat user pada IAM

| Permissions policies |
|--|
| **AWSGreengrassFullAccess** |
| **AWSIoTFullAccess** |
| **IAMFullAccess** |

#### Create Access keys

## 2. Install Program Java Pada OS

#### Install Package Manager on Amazon Linux 2

Option 1: Install headless Amazon Corretto 11:
```sh
sudo yum install java-11-amazon-corretto-headless -y
```

Option 2: Install the full Amazon Corretto 11:
```sh
sudo yum install java-11-amazon-corretto -y
```

#### Verifikasi Instalasi

Verifikasi
```sh
sudo alternatives --config java
```

Cek Java
```sh
java -version
```

Source :
- 👉 [**Instalasing Java**](https://docs.aws.amazon.com/corretto/latest/corretto-11-ug/amazon-linux-install.html)
- 👉 [**Install Java in Other OS**](https://docs.aws.amazon.com/greengrass/v2/developerguide/getting-started-set-up-environment.html)


## 3. Install the AWS IoT Greengrass Core software (console)

#### Export kredensial AWS
```sh
export AWS_ACCESS_KEY_ID=<AWS_ACCESS_KEY_ID>
export AWS_SECRET_ACCESS_KEY=<AWS_SECRET_ACCESS_KEY>
export AWS_SESSION_TOKEN=<AWS_SESSION_TOKEN> // Opsional
```

#### Download installer

Samakan dengan Cara install nya, Example :
```sh
curl -s https://d2s8p88vqu9w66.cloudfront.net/releases/greengrass-nucleus-latest.zip > greengrass-nucleus-latest.zip && unzip greengrass-nucleus-latest.zip -d GreengrassInstaller
```

Jalankan Installer
```sh
sudo -E java -Droot="/greengrass/v2" -Dlog.store=FILE -jar ./GreengrassInstaller/lib/Greengrass.jar --aws-region us-east-1 --thing-name GreengrassDevice  --component-default-user ggc_user:ggc_group --provision true --setup-system-service true --deploy-dev-tools true
```

#### Run the Greengrass software

```sh
sudo /greengrass/v2/alts/current/distro/bin/loader
```

Output :
```
Launched Nucleus successfully.
```

#### Verifikasi instalasi CLI Greengrass

Secara otomatis akan membuat Things pada IoT Core, gunakan pada perintah ini
```sh
aws greengrassv2 list-effective-deployments --core-device-thing-name <MyGreengrassCore>
```

## 4. Develop dan test pada component di device

#### Buat 2 directory recipes dan artifacts
```sh
mkdir -p ~/greengrassv2/{recipes,artifacts}
cd ~/greengrassv2
```

#### Buat script JSON

Digunakan untuk mendefinisikan component's metadata, parameters, dependencies, lifecycle, and kemampuan platform komponen.
```sh
nano recipes/com.example.HelloWorld-1.0.0.json
```

Tambahkan Menggunakan Script ini 👇:
- Script JSON : [**Hellow World.JSON**](./linux_file/com.example.HelloWorld-1.0.0.json)

**`Notes :`**
- **ComponentConfiguration** : menentukan parameter, Message, yang default -nya adalah world
- **Manifests** : serangkaian lifecycle instructions dan artifact untuk platform.
    - Bagian `Lifecycle` memerintahkan perangkat inti Greengrass untuk menjalankan skrip Hello World dengan nilai parameter Message sebagai argumen.


#### Buat folder untuk komponen artifact

```sh
mkdir -p artifacts/com.example.HelloWorld/1.0.0
```

- **⚠ Important**

    Anda harus menggunakan format berikut untuk jalur folder artifact.
    ```
    artifacts/componentName/componentVersion/
    ```

#### Buat file artefak skrip Python untuk komponen Hello World

```sh
nano artifacts/com.example.HelloWorld/1.0.0/hello_world.py
```

Tambahkan Menggunakan Script python 👇:
- Script .py : [**hello_world.py**](linux_file/hello_world.py)

#### Jalankan perintah berikut untuk men-deploy komponen tersebut ke AWS IoT Greengrass Core

```sh
sudo /greengrass/v2/bin/greengrass-cli deployment create \
  --recipeDir ~/greengrassv2/recipes \
  --artifactDir ~/greengrassv2/artifacts \
  --merge "com.example.HelloWorld=1.0.0"
```

#### Periksa log lagi untuk memverifikasi bahwa komponen Hello World mencetak pesan baru

```sh
sudo tail -f /greengrass/v2/logs/com.example.HelloWorld.log
```

Output :

pesan yang mirip dengan contoh berikut ini.
```
Hello, world! Greetings from your first Greengrass component.
```

- **⚠ Important**

    Jalankan perintah berikut untuk memperbarui komponen dengan perubahan
    ```
    sudo /greengrass/v2/bin/greengrass-cli deployment create \
        --recipeDir ~/greengrassv2/recipes \
        --artifactDir ~/greengrassv2/artifacts \
        --merge "com.example.HelloWorld=1.0.0"
    ```

    Jalankan perintah berikut untuk me-restart komponen.
    ```
    sudo /greengrass/v2/bin/greengrass-cli component restart \
        --names "com.example.HelloWorld"
    ```

#### Perbarui parameter konfigurasi komponen untuk menguji konfigurasi yang berbeda.

```sh
sudo nano hello-world-config-update.json
```

Salin dan tempel objek JSON berikut ke dalam file. Objek JSON ini menentukan pembaruan konfigurasi yang menggabungkan nilai friend ke parameter Message untuk memperbarui nilainya.

```sh
{
  "com.example.HelloWorld": {
    "MERGE": {
      "Message": "friend"
    }
  }
}
```

Jalankan perintah berikut untuk men-deploy pembaruan konfigurasi

```sh
sudo /greengrass/v2/bin/greengrass-cli deployment create \
  --merge "com.example.HelloWorld=1.0.0" \
  --update-config hello-world-config-update.json
```

Periksa log lagi untuk memverifikasi bahwa komponen Hello World mengeluarkan pesan baru

```sh
sudo tail -f /greengrass/v2/logs/com.example.HelloWorld.log
```

Output :

```
Hello, friend! Greetings from your first Greengrass component.
```

#### Setelah Anda selesai menguji komponen, lepaskan komponen tersebut dari perangkat inti Anda. Jalankan perintah berikut

```sh
sudo /greengrass/v2/bin/greengrass-cli deployment create --remove="com.example.HelloWorld"
```

Jalankan perintah berikut dan verifikasi bahwa perintah com.example.HelloWorld

```sh
sudo /greengrass/v2/bin/greengrass-cli component list
```

## 5. Buat component di AWS IoT Greengrass service

#### Buat S3 pada AWS

Uploud Folder [**`artifacts`**](artifacts)

![giphy (1)](https://github.com/SonyVansha/Internet_of_Things_in_AWS/assets/152833966/a812f0d7-f2e3-4864-8feb-31c66b339c10)

#### Buat policy pada IAM dengan Nama MyGreengrassV2ComponentArtifactPolicy

Pada Tab **JSON**, gunakan code ini untuk mengakses S3 Bucket
```sh
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": [
        "s3:GetObject"
      ],
      "Resource": "arn:aws:s3:::DOC-EXAMPLE-BUCKET/*"
    }
  ]
}
```

#### Pada AWS IoT Greengrass konsol Tambahakan Code Ini

Pada Tab **Components**, masukan code JSON

```sh
{
  "RecipeFormatVersion": "2020-01-25",
  "ComponentName": "com.example.HelloWorld",
  "ComponentVersion": "1.0.0",
  "ComponentDescription": "My first AWS IoT Greengrass component.",
  "ComponentPublisher": "Amazon",
  "ComponentConfiguration": {
    "DefaultConfiguration": {
      "Message": "world"
    }
  },
  "Manifests": [
    {
      "Platform": {
        "os": "linux"
      },
      "Lifecycle": {
        "run": "python3 -u {artifacts:path}/hello_world.py \"{configuration:/Message}\""
      },
      "Artifacts": [
        {
          "URI": "s3://DOC-EXAMPLE-BUCKET/artifacts/com.example.HelloWorld/1.0.0/hello_world.py"
        }
      ]
    },
    {
      "Platform": {
        "os": "windows"
      },
      "Lifecycle": {
        "run": "py -3 -u {artifacts:path}/hello_world.py \"{configuration:/Message}\""
      },
      "Artifacts": [
        {
          "URI": "s3://DOC-EXAMPLE-BUCKET/artifacts/com.example.HelloWorld/1.0.0/hello_world.py"
        }
      ]
    }
  ]
}
```

## 6. Deploy component

### Cara Deploy Di :
👉 [**`Deploy Component To IoT`**](https://docs.aws.amazon.com/id_id/greengrass/v2/developerguide/deploy-first-component.html)

## Done
