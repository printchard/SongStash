# SongStash

SongStash is a project with the objective to share song lyrics amongst its users.

## What is it?

SongStash is a service built with a Server-Client architecture, that lets users upload lyrics to songs the know, being able to share them with other users. The server uses sqlite to store the data.

## How to use it?

If you want to get started, first use Makefile to build the server.

```console
make server
```

Then, you can run the server with the following comand:

```console
./server <port>
```

After making sure the server is up and running, you can build the client with the Makefile:

```console
make client
```

In order for the client to work, you need to configure it. Try configuring it with the following commands:

```console
./client config set url localhost
./client config set port <port>
```

Finally, the client is ready for use. Try the `lookup` command:

```console
./client lookup
```

If you want to try other commands, you can use the `help` command to learn more about the cli.
