# Just notes for developers

I'm making notes here so I don't forget about something. You can also add or correct outdated information! `:)`

## Salt
Secvault uses salt for security, it can be specified on the infra in the following ways:

```bash
export SECV_SALT="secret_salt"
# or
docker run -e SECV_SALT="secret_salt" {image}
```

`!` Yoy can find the salt in the code in the `common/sys.h` file with `Environment` struct.

## PoomPoomPoom

`~~~`
