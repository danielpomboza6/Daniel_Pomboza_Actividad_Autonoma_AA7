#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// PROTOTIPOS
void mostrarMenu();
int leerEntero(string mensaje, int min, int max);
void guardarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos);
void insertarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos);
void actualizarPrestamo(vector<vector<int>>& stock, vector<vector<int>>& prestamos);
void mostrarDisponibles(const vector<vector<string>>& libros, const vector<vector<int>>& stock);
void modificarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock);
void eliminarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos);
void buscarLibro(const vector<vector<string>>& libros);
void ordenarLibros(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos);
void reporteAvanzado(const vector<vector<string>>& libros, const vector<vector<int>>& stock, const vector<vector<int>>& prestamos);

int main() {
    vector<vector<string>> libros;
    vector<vector<int>> stock;
    vector<vector<int>> prestamos;

    int opcion;
    do {
        mostrarMenu();
        opcion = leerEntero("Seleccione una opcion: ", 1, 10);

        switch (opcion) {
            case 1: guardarLibro(libros, stock, prestamos); break;
            case 2: insertarLibro(libros, stock, prestamos); break;
            case 3: actualizarPrestamo(stock, prestamos); break;
            case 4: mostrarDisponibles(libros, stock); break;
            case 5: modificarLibro(libros, stock); break;
            case 6: eliminarLibro(libros, stock, prestamos); break;
            case 7: buscarLibro(libros); break;
            case 8: ordenarLibros(libros, stock, prestamos); break;
            case 9: reporteAvanzado(libros, stock, prestamos); break;
        }
    } while (opcion != 10);

    return 0;
}

// VALIDACIÓN
int leerEntero(string mensaje, int min, int max) {
    int num;
    while (true) {
        cout << mensaje;
        if (cin >> num && num >= min && num <= max) {
            cin.ignore();
            return num;
        }
        cout << "Entrada invalida.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

void mostrarMenu() {
    cout << "\nGESTION DE BIBLIOTECA\n";
    cout << "1. Guardar libro\n2. Insertar libro\n3. Registrar prestamo\n";
    cout << "4. Mostrar disponibles\n5. Modificar libro\n6. Eliminar libro\n";
    cout << "7. Buscar libro\n8. Ordenar libros\n9. Reporte\n10. Salir\n";
}

// FUNCIONES

void guardarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos) {
    string nombre, cat;
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Categoria: "; getline(cin, cat);
    int cant = leerEntero("Stock: ", 0, 1000);

    libros.push_back({nombre, cat});
    stock.push_back({cant, 0});
    prestamos.push_back(vector<int>(5, 0));
}

void insertarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos) {
    int pos = leerEntero("Posicion: ", 0, libros.size());
    string nombre, cat;
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Categoria: "; getline(cin, cat);
    int cant = leerEntero("Stock: ", 0, 1000);

    libros.insert(libros.begin() + pos, {nombre, cat});
    stock.insert(stock.begin() + pos, {cant, 0});
    prestamos.insert(prestamos.begin() + pos, vector<int>(5, 0));
}

void actualizarPrestamo(vector<vector<int>>& stock, vector<vector<int>>& prestamos) {
    if (stock.empty()) return;
    int id = leerEntero("ID libro: ", 0, stock.size() - 1);

    if (stock[id][0] > 0) {
        int dia = leerEntero("Dia (0=Lun a 4=Vie): ", 0, 4);
        stock[id][0]--;
        stock[id][1]++;
        prestamos[id][dia]++;
    }
}

void mostrarDisponibles(const vector<vector<string>>& libros, const vector<vector<int>>& stock) {
    for (size_t i = 0; i < libros.size(); i++) {
        if (stock[i][0] > 0)
            cout << i << " - " << libros[i][0] << " (" << stock[i][0] << ")\n";
    }
}

void modificarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock) {
    int id = leerEntero("ID: ", 0, libros.size() - 1);
    cout << "Nuevo nombre: "; getline(cin, libros[id][0]);
    cout << "Nueva categoria: "; getline(cin, libros[id][1]);
    stock[id][0] = leerEntero("Nuevo stock: ", 0, 1000);
}

void eliminarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos) {
    int id = leerEntero("ID: ", 0, libros.size() - 1);
    libros.erase(libros.begin() + id);
    stock.erase(stock.begin() + id);
    prestamos.erase(prestamos.begin() + id);
}

// FIND
void buscarLibro(const vector<vector<string>>& libros) {
    string criterio;
    cout << "Buscar: "; getline(cin, criterio);

    bool encontrado = false;
    for (size_t i = 0; i < libros.size(); i++) {
        if (find(libros[i].begin(), libros[i].end(), criterio) != libros[i].end()) {
            cout << "ID " << i << ": " << libros[i][0] << " [" << libros[i][1] << "]\n";
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No encontrado.\n";
}

// SORT
void ordenarLibros(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos) {
    int tipo = leerEntero("1.Nombre 2.Stock 3.Prestamos: ", 1, 3);

    vector<int> idx(libros.size());
    for (int i = 0; i < idx.size(); i++) idx[i] = i;

    sort(idx.begin(), idx.end(), [&](int a, int b) {
        if (tipo == 1) return libros[a][0] < libros[b][0];
        if (tipo == 2) return stock[a][0] < stock[b][0];
        return stock[a][1] < stock[b][1];
    });

    auto L = libros;
auto S = stock;
auto P = prestamos;

    for (int i = 0; i < idx.size(); i++) {
        libros[i] = L[idx[i]];
        stock[i] = S[idx[i]];
        prestamos[i] = P[idx[i]];
    }
}

// REPORTE
void reporteAvanzado(const vector<vector<string>>& libros, const vector<vector<int>>& stock, const vector<vector<int>>& prestamos) {
    vector<int> totalDia(5, 0);
    int maxLibro = 0, idx = 0;

    for (int i = 0; i < libros.size(); i++) {
        int suma = 0;
        for (int j = 0; j < 5; j++) {
            suma += prestamos[i][j];
            totalDia[j] += prestamos[i][j];
        }
        if (suma > maxLibro) {
            maxLibro = suma;
            idx = i;
        }
        if (stock[i][0] == 0)
            cout << libros[i][0] << " AGOTADO\n";
    }

    int dia = max_element(totalDia.begin(), totalDia.end()) - totalDia.begin();
    cout << "Libro mas prestado: " << libros[idx][0] << endl;
    cout << "Dia mas activo: " << dia << endl;
}
