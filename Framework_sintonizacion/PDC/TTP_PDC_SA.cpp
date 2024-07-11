#include <iostream>
#include <vector>
#include <fstream> 
#include <random>
#include "../Algoritmos/algoritmos_TTP.cpp"
#include <sstream>
#include <iterator>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){

    int contador_fila = 0;

    int numero_solicitudes;
    int cantidad_equipos;
    int fecha_limite_vacaciones;

    vector<int> equipos_fuertes;
    vector<int> equipos_libertadores;
    vector<int> equipos_prelibertadores;
    vector<int> equipos_sudamericana;

    vector<int> equipos_zona_norte;
    vector<int> equipos_zona_centro;
    vector<int> equipos_zona_sur;
    vector<int> equipos_zonas_vacaciones;
    vector<int> equipos_santiago;

    vector<int> fechas_previas_prelibertadores;
    vector<int> fechas_posteriores_prelibertadores;
    vector<int> fechas_previas_libertadores;
    vector<int> fechas_posteriores_libertadores;
    vector<int> fechas_previas_sudamericana;
    vector<int> fechas_posteriores_sudamericana;
    
    vector<vector<int>> solicituedes_visitante;

    // ----------------------------------------------------- LECTURA INSTANCIA ------------------------------------------------------

    ifstream file("instanciaPDC.txt");

    string line;

    if (file.is_open()) { 
        while (getline(file, line)) { 
            if (contador_fila == 0){
                cantidad_equipos = stoi(line);
                //cout << "Cantidad de equipos: " << cantidad_equipos << endl;
            }
            else if (contador_fila == 1){ // equipos fuertes
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_fuertes.push_back(stoi(vstrings[i]));
                }
            }
            else if(contador_fila == 2){ // equipos libertadores
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_libertadores.push_back(stoi(vstrings[i]));
                }
            }
            else if(contador_fila == 3){ // equipos pre libertadores
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_prelibertadores.push_back(stoi(vstrings[i]));
                }
            }
            else if(contador_fila == 4){ // equipos sudamericana
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_sudamericana.push_back(stoi(vstrings[i]));
                }
            }
            else if(contador_fila == 5){ // equipos zona norte
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_zona_norte.push_back(stoi(vstrings[i]));
                }
            }
            else if(contador_fila == 6){ // equipos zona centro
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_zona_centro.push_back(stoi(vstrings[i]));
                }
            }
            else if(contador_fila == 7){ // equipos zona sur
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_zona_sur.push_back(stoi(vstrings[i]));
                }
            }
            else if(contador_fila == 8){ // equipos zona vacaciones
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_zonas_vacaciones.push_back(stoi(vstrings[i]));
                }  
            }
            else if (contador_fila == 9){ // equipos de santiago
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_santiago.push_back(stoi(vstrings[i]));
                }  
            }
            else if (contador_fila == 10){ // fechas previas pre libertadores
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_previas_prelibertadores.push_back(stoi(vstrings[i]));
                }  
            }
            else if (contador_fila == 11){ // fechas posteriores pre libertadores
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_posteriores_prelibertadores.push_back(stoi(vstrings[i]));
                }  
            }
            else if (contador_fila == 12){ // fechas previas libertadores
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_previas_libertadores.push_back(stoi(vstrings[i]));
                }  
            }
            else if (contador_fila == 13){ // fechas posteriores libertadores
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_posteriores_libertadores.push_back(stoi(vstrings[i]));
                }  
            }
            else if (contador_fila == 14){ // fechas previas sudamericana
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_previas_sudamericana.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == 15){ // fechas posteriores sudamericana
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_posteriores_sudamericana.push_back(stoi(vstrings[i]));
                }
            }
            else if(contador_fila == 16){
                fecha_limite_vacaciones = stoi(line);
            }
            else if (contador_fila == 17){ // solicitudes visitante
                numero_solicitudes = stoi(line);
            }
            else{
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end);
                vector<int> aux_solicitud;
                aux_solicitud.clear();
                for (int i = 0; i < vstrings.size(); i++){
                    aux_solicitud.push_back(stoi(vstrings[i]));
                }
                solicituedes_visitante.push_back(aux_solicitud);
            }
            contador_fila++;
        }
    }
    else { 
        cout << "Unable to open file\n";
    }

    // se asume que los equipos participantes en pre libertadores van a acceder a libertadores

    for (int i = 0; i < equipos_prelibertadores.size(); i++){
        equipos_libertadores.push_back(equipos_prelibertadores[i]);
    }

    // -------------------------------------------------- FIN LECTURA INSTANCIA ------------------------------------------------------

    // generando calendarizacion inicial

    vector<vector<int>> rueda1_inicial = creacion_fixture_inicial(16);
    vector<vector<int>> rueda2_inicial = generacion_rueda_mirrored(rueda1_inicial);

    //print_calendarizacion(rueda1_inicial, rueda2_inicial);

    // parametros SA
    int tempertura; //1000
    float tasa_enfriamiento; //0.8
    int cambios_temperatura; //15
    int cantidad_iteraciones;

    //lectura de parametros

    for (int i = 0; i <=4; i++){
        if(i == 1){
            cantidad_iteraciones = stoi(argv[1]);
        }
        else if(i == 2){
            tempertura = stoi(argv[2]);
        }
        else if(i == 3){
            tasa_enfriamiento = stof(argv[3]);
        }
        else if(i == 4){
            cambios_temperatura = stoi(argv[4]);
        }
    }

    //forzando que tasa_enfriamiento sea decimal

    while (tasa_enfriamiento > 1){
        tasa_enfriamiento = tasa_enfriamiento/10;
    }

    //cout << cantidad_iteraciones << " " << tempertura << " " << tasa_enfriamiento << " " << cambios_temperatura << endl;

    vector<vector<vector<int>>> ruedas_SA = sa_pdc(rueda1_inicial, rueda2_inicial, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, 
    equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, equipos_zonas_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, 
    fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana, fechas_posteriores_sudamericana, solicituedes_visitante, tempertura, cantidad_iteraciones, tasa_enfriamiento, cambios_temperatura);

    //cout << "Fin SA" << endl;

    vector<vector<int>> rueda1_SA = ruedas_SA[0];
    vector<vector<int>> rueda2_SA = ruedas_SA[1];
    
    int evaluacion_actual_SA = funcion_evaluacion_pdc(rueda1_SA, rueda2_SA, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, 
    equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, equipos_zonas_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, 
    fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana, fechas_posteriores_sudamericana, solicituedes_visitante);

    bool info_completa = false;

    if (!info_completa){
        cout << evaluacion_actual_SA << endl;
    }
    else{

        //imprimiendo parametros
        /*
        cout << "Parametros SA" << endl;
        cout << "Cantidad de iteraciones: " << cantidad_iteraciones << endl;
        cout << "Temperatura inicial: " << tempertura << endl;
        cout << "Tasa de enfriamiento: " << tasa_enfriamiento << endl;
        cout << "Cambios de temperatura: " << cambios_temperatura << endl;
        */

        print_calendarizacion(rueda1_SA, rueda2_SA);
        cout << "\nFixture PDC SA" << endl;
        cout << "Valor evaluacion: " << evaluacion_actual_SA << endl;

        cout << "\nCosto de restricciones" << endl;
        print_costo_restricciones_pdc(rueda1_SA, rueda2_SA, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores,
        equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, equipos_zonas_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores,
        fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana, fechas_posteriores_sudamericana, solicituedes_visitante);

        // revisiones que este correcto el fixture respecto a restricciones base
        
        cout << "\n";

        //cout << "Rueda 1" << endl;

        for (int i = 0; i < 15; i++){
            int contador = 0;
            for (int j = 0; j < 16; j++){
                if (rueda1_SA[j][i] < 0){
                    contador++;
                }
            }
            //cout << "Fecha " << i+1 << ": " << contador << endl;
        }

        //cout << "Rueda 2" << endl;

        for (int i = 0; i < 15; i++){
            int contador = 0;
            for (int j = 0; j < 16; j++){
                if (rueda2_SA[j][i] < 0){
                    contador++;
                }
            }
            //cout << "Fecha " << i+1 << ": " << contador << endl;
        }

        int contador_errores_localias_inversas = 0;

        //revisando que las localias esten invertidas por equipos
        for (int i = 0; i < 16; i++){
            for (int j = 0; j < 15; j++){ //rueda1
                int rival_primera_rueda = abs(rueda1_SA[i][j]);
                for (int k = 0; k < 15; k++){ // rueda2
                    if (abs(rueda2_SA[i][k]) == rival_primera_rueda){
                        if (rueda1_SA[i][j] > 0 && rueda2_SA[i][k] > 0 || rueda1_SA[i][j] < 0 && rueda2_SA[i][k] < 0){
                            cout << "Error en localias inversas equipos " << i+1 << " y " << rival_primera_rueda << endl;
                            contador_errores_localias_inversas++;
                        }
                    }
                }
            }
        }
        

        cout << "Errores encontrados: " << contador_errores_localias_inversas << endl;

        int contador_errores_sumatoria_columna = 0;
        int suma_col;

        //rueda 1
        for (int i = 0; i < 15; i++){ // por fecha
            suma_col = 0;
            for (int j = 0; j < 16; j++){ // por equipo
                suma_col += abs(rueda1_SA[j][i]);
            }
            if (suma_col != 136){
                cout << "Error en la suma de la fecha " << i+1 << endl;
                contador_errores_sumatoria_columna++;
            }
        }

        //rueda 2
        for (int i = 0; i < 15; i++){ // por fecha
            suma_col = 0;
            for (int j = 0; j < 16; j++){ // por equipo
                suma_col += abs(rueda2_SA[j][i]);
            }
            if (suma_col != 136){
                cout << "Error en la suma de la fecha " << i+20 << endl;
                contador_errores_sumatoria_columna++;
            }
        }

        cout << "Errores encontrados suma fecha: " << contador_errores_sumatoria_columna << endl;

        //revision de que en cada rueda un equipo se enfrente a todos los demas
        vector<int> equipos_enfrentados = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        for (int i = 0; i <16; i++){
            //rueda 1
            vector<int> rivales_aux = equipos_enfrentados;
            auto it = std::find(rivales_aux.begin(), rivales_aux.end(), i+1); 
            if (it != rivales_aux.end()) { 
                rivales_aux.erase(it); 
            }
            for(int j = 0; j < 15; j++){
                auto it2 = std::find(rivales_aux.begin(), rivales_aux.end(), abs(rueda1_SA[i][j])); 
                if (it2 != rivales_aux.end()) { 
                    rivales_aux.erase(it2); 
                }
            }
            if (rivales_aux.size() != 0){
                cout << "Error en rueda 1, equipo " << i+1 << " no se enfrenta a todos los demas" << endl;
            }
            //rueda 2
            rivales_aux = equipos_enfrentados;
            auto it3 = std::find(rivales_aux.begin(), rivales_aux.end(), i+1);
            if (it3 != rivales_aux.end()) { 
                rivales_aux.erase(it3); 
            }
            for(int j = 0; j < 15; j++){
                auto it4 = std::find(rivales_aux.begin(), rivales_aux.end(), abs(rueda2_SA[i][j])); 
                if (it4 != rivales_aux.end()) { 
                    rivales_aux.erase(it4); 
                }
            }
            if (rivales_aux.size() != 0){
                cout << "Error en rueda 2, equipo " << i+1 << " no se enfrenta a todos los demas" << endl;
            }
        }

        //revision de consistencia por fecha
        // si i juega contra j, entonces j debe jugar contra i (ademas los signos deben ser contrarios)

        int error_consistencia_fecha = 0;

        //revisando rueda 1
        for (int j = 0; j < 15; j++){
            for (int i = 0; i < 16; i++){
                int rival = abs(rueda1_SA[i][j]);

                // rival debe jugar contra i+1
                if(abs(rueda1_SA[rival-1][j]) != i+1){
                    cout << "Error en consistencia de fecha " << j+1 << " entre equipos " << i+1 << " y " << rival << ", el equipo " << rival << " no enfrenta a " << i+1 << endl;
                    error_consistencia_fecha++; 
                }

                // signos deben ser contrarios    
                if (rueda1_SA[i][j] > 0 && rueda1_SA[rival-1][j] > 0 || rueda1_SA[i][j] < 0 && rueda1_SA[rival-1][j] < 0){
                    cout << "Error en consistencia de fecha " << j+1 << " entre equipos " << i+1 << " y " << rival << ", ambos tienen la misma condicion" << endl;
                    error_consistencia_fecha++;
                }
            }
        }

        //revisando rueda 2
        for (int j = 0; j < 15; j++){
            for (int i = 0; i < 16; i++){
                int rival = abs(rueda2_SA[i][j]);
                // rival debe jugar contra i+1
                if(abs(rueda2_SA[rival-1][j]) != i+1){
                    cout << "Error en consistencia de fecha " << j+17 << " entre equipos " << i+1 << " y " << rival << ", el equipo " << rival << " no enfrenta a " << i+1 << endl;
                    error_consistencia_fecha++; 
                }

                // signos deben ser contrarios    
                if (rueda2_SA[i][j] > 0 && rueda2_SA[rival-1][j] > 0 || rueda2_SA[i][j] < 0 && rueda2_SA[rival-1][j] < 0){
                    cout << "Error en consistencia de fecha " << j+17 << " entre equipos " << i+1 << " y " << rival << ", ambos tienen la misma condicion" << endl;
                    error_consistencia_fecha++;
                }
            }
        }
        
        cout << "Errores en consistencia de fecha: " << error_consistencia_fecha << endl;

    }
}