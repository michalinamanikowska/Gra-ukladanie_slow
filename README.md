Sposób budoawnia oraz uruchamiania projektu:
1. W terminalu przechodzimy do folderu z grą
2. Wykonujemy następujące polecenia:
    mkdir build
    cd build
    cmake ..
    make
3. Znajdujemy się w folderze build w którym są także dwa folredy: Client i Server. W zależności czy chcemy uruchomić klienta czy serwer wybieramy odpowiednio:
    dla serwera:
        cd Server
        ./server
    dla klienta:
        cd Client
        ./Client

