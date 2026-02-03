#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

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

        if (opcion >= 2 && opcion <= 9 && opcion != 2 && libros.empty()) {
            cout << "\n[!] Error: No hay libros registrados aun.\n";
            continue;
        }

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

int leerEntero(string mensaje, int min, int max) {
    int num;
    while (true) {
        cout << mensaje;
        if (cin >> num) {
            if (num >= min && num <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                return num;
            }
        }
        cout << "[Error] Entrada invalida. Rango permitido: [" << min << " - " << max << "]\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void mostrarMenu() {
    cout << "   GESTION DE BIBLIOTECA\n";
    cout << "1. Guardar libro\n2. Insertar en posicion\n3. Registrar prestamo\n";
    cout << "4. Mostrar disponibles\n5. Modificar libro\n6. Eliminar libro\n";
    cout << "7. Buscar libro\n8. Ordenar libros\n9. Reporte\n10. Salir\n";
}


void guardarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos) {
    string nombre, cat;
    cout << "Nombre del libro: "; getline(cin, nombre);
    cout << "Categoria: "; getline(cin, cat);
    int cant = leerEntero("Cantidad inicial en Stock: ", 0, 1000);

    libros.push_back({nombre, cat});
    stock.push_back({cant, 0});
    prestamos.push_back(vector<int>(5, 0));
}

void insertarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos) {
    int pos = leerEntero("Posicion a insertar: ", 0, (int)libros.size());
    
    string nombre, cat;
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Categoria: "; getline(cin, cat);
    int cant = leerEntero("Stock: ", 0, 1000);

    libros.insert(libros.begin() + pos, {nombre, cat});
    stock.insert(stock.begin() + pos, {cant, 0});
    prestamos.insert(prestamos.begin() + pos, vector<int>(5, 0));
}

void actualizarPrestamo(vector<vector<int>>& stock, vector<vector<int>>& prestamos) {
    int id = leerEntero("ID libro a prestar: ", 0, (int)stock.size() - 1);

    if (stock[id][0] > 0) {
        int dia = leerEntero("Dia (0=Lun, 1=Mar, 2=Mie, 3=Jue, 4=Vie): ", 0, 4);
        stock[id][0]--;
        stock[id][1]++;
        prestamos[id][dia]++;
        cout << "Prestamo registrado con exito.\n";
    } else {
        cout << "[!] No hay stock disponible de este libro.\n";
    }
}

void mostrarDisponibles(const vector<vector<string>>& libros, const vector<vector<int>>& stock) {
    cout << "\n LIBROS DISPONIBLES \n";
    bool hay = false;
    for (size_t i = 0; i < libros.size(); i++) {
        if (stock[i][0] > 0) {
            cout << "ID " << i << ": " << libros[i][0] << " | Stock: " << stock[i][0] << "\n";
            hay = true;
        }
    }
    if (!hay) cout << "No hay libros con stock actualmente.\n";
}

void modificarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock) {
    int id = leerEntero("ID del libro a modificar: ", 0, (int)libros.size() - 1);
    cout << "Nuevo nombre: "; getline(cin, libros[id][0]);
    cout << "Nueva categoria: "; getline(cin, libros[id][1]);
    stock[id][0] = leerEntero("Nuevo stock: ", 0, 1000);
}

void eliminarLibro(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos) {
    int id = leerEntero("ID del libro a eliminar: ", 0, (int)libros.size() - 1);
    libros.erase(libros.begin() + id);
    stock.erase(stock.begin() + id);
    prestamos.erase(prestamos.begin() + id);
    cout << "Libro eliminado correctamente.\n";
}

void buscarLibro(const vector<vector<string>>& libros) {
    string criterio;
    cout << "Ingrese nombre o categoria a buscar: "; getline(cin, criterio);

    bool encontrado = false;
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i][0].find(criterio) != string::npos || libros[i][1].find(criterio) != string::npos) {
            cout << "ID " << i << ": " << libros[i][0] << " [" << libros[i][1] << "]\n";
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontro ningun resultado.\n";
}

void ordenarLibros(vector<vector<string>>& libros, vector<vector<int>>& stock, vector<vector<int>>& prestamos) {
    cout << "Ordenar por: 1.Nombre | 2.Stock | 3.Total Prestamos\n";
    int tipo = leerEntero("Seleccione: ", 1, 3);

    vector<int> idx(libros.size());
    for (int i = 0; i < (int)idx.size(); i++) idx[i] = i;

    sort(idx.begin(), idx.end(), [&](int a, int b) {
        if (tipo == 1) return libros[a][0] < libros[b][0];
        if (tipo == 2) return stock[a][0] < stock[b][0];
        return stock[a][1] > stock[b][1];
    });

    auto L = libros;
    auto S = stock;
    auto P = prestamos;

    for (int i = 0; i < (int)idx.size(); i++) {
        libros[i] = L[idx[i]];
        stock[i] = S[idx[i]];
        prestamos[i] = P[idx[i]];
    }
    cout << "Lista ordenada satisfactoriamente.\n";
}

void reporteAvanzado(const vector<vector<string>>& libros, const vector<vector<int>>& stock, const vector<vector<int>>& prestamos) {
    vector<int> totalDia(5, 0);
    int maxPrestamos = -1, idxMax = 0;

    cout << "\nREPORTE ESTATICO\n";
    for (int i = 0; i < (int)libros.size(); i++) {
        int sumaLibro = 0;
        for (int j = 0; j < 5; j++) {
            sumaLibro += prestamos[i][j];
            totalDia[j] += prestamos[i][j];
        }
        
        if (sumaLibro > maxPrestamos) {
            maxPrestamos = sumaLibro;
            idxMax = i;
        }

        if (stock[i][0] == 0)
            cout << "[!] AGOTADO: " << libros[i][0] << endl;
    }

    int maxDiaVal = -1, diaActivo = 0;
    string dias[] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes"};
    
    for(int i=0; i<5; i++) {
        if(totalDia[i] > maxDiaVal) {
            maxDiaVal = totalDia[i];
            diaActivo = i;
        }
    }

    if (!libros.empty()) {
        cout << "Libro mas solicitado: " << libros[idxMax][0] << " (" << maxPrestamos << " prestamos)\n";
        cout << "Dia de mayor actividad: " << dias[diaActivo] << " (" << maxDiaVal << " prestamos)\n";
    }
}