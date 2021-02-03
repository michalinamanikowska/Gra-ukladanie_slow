Sposób budowania oraz uruchamiania projektu:
1. W terminalu przechodzimy do folderu z grą
2. Wykonujemy następujące polecenia:  <br />
    mkdir build <br />
    cd build  <br />
    cmake ..  <br />
    make  <br />
3. Znajdujemy się w folderze build w którym są także dwa foldery: Client i Server. W zależności czy chcemy uruchomić klienta czy serwer wybieramy odpowiednio:
    dla serwera:  <br />
        cd Server  <br />
        ./server  <br />
    dla klienta:  <br />
        cd Client  <br />
        ./Client  <br />

