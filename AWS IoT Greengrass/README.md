# Greengrass devices

### 1. Buat user pada IAM

| Permissions policies |
|--|
| **AWSGreengrassFullAccess** |
| **AWSIoTFullAccess** |
| **IAMFullAccess** |

#### Create Access keys

### 2. Install Program Java Pada OS

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


### 3. Install the AWS IoT Greengrass Core software (console)

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

### 4. Develop dan test pada component di device

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
- Script JSON : [**Hellow World.JSON**](./com.example.HelloWorld-1.0.0.json)

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
- Script .py : [**hello_world.py**](./hello_world.py)

#### Jalankan perintah berikut untuk men-deploy komponen tersebut ke AWS IoT Greengrass Core

```sh
sudo /greengrass/v2/bin/greengrass-cli deployment create \
  --recipeDir ~/greengrassv2/recipes \
  --artifactDir ~/greengrassv2/artifacts \
  --merge "com.example.HelloWorld=1.0.0"
```

Output :

pesan yang mirip dengan contoh berikut ini.
```sh
nano artifacts/com.example.HelloWorld/1.0.0/hello_world.py
```