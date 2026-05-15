# Doxygen

### Install Doxygen

```bash
sudo apt update && sudo apt upgrade
sudo apt install doxygen
```

### Generate the html

```bash
doxygen doxygen_config
```

### Run the Doxygen

```bash
cd html
python3 -m html/http.server [PORT]
```

### Example

```bash
cd html
python3 -m html/http.server 8080
```
