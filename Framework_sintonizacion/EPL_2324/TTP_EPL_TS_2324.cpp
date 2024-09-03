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
    vector<int> aux_distancias;

    int cantidad_equipos;
    int fecha_boxing_day;
    int fecha_new_year;
    int distancia_optima;
    vector<int> equipos_fuertes;
    vector<int> equipos_UCL;
    vector<int> equipos_UEL;
    vector<int> equipos_UECL;
    vector<int> equipos_emparejados;
    vector<int> fechas_previas_FA_Cup;
    vector<int> fechas_posteriores_FA_Cup;
    vector<int> fechas_previas_UCL;
    vector<int> fechas_posteriores_UCL;
    vector<int> fechas_previas_UEL;
    vector<int> fechas_posteriores_UEL;
    vector<int> fechas_previas_UECL;
    vector<int> fechas_posteriores_UECL;
    vector<int> fechas_bank_holidays;
    vector<vector<int>> solicituedes_visitante; // tuplas [equipo,fecha]
    vector<vector<int>> distancias;

    // ---------------------------------------------------- LECTURA PARAMETROS ------------------------------------------------------

    // parametros TS

    string nombre_archivo;
    int semilla;
    int iteraciones;
    vector<int> largos_listas_equipos;
    vector<int> largos_listas_fechas;
    vector<vector<int>>  probabilidades_operadores = {{},{},{}};

    //lectura de parametros

    for (int i = 0; i <= 24; i++){

        if (i == 1){
            nombre_archivo = argv[i];
        }
        else if (i == 2){
            semilla = stoi(argv[i]);
        }
        else if (i == 3){
            iteraciones = stoi(argv[i]);
        }
        else if (i >= 4 && i <= 6){
            largos_listas_equipos.push_back(stoi(argv[i]));
        }
        else if (i >= 7 && i <= 9){
            largos_listas_fechas.push_back(stoi(argv[i]));
        }
        else if (i >= 10 && i <= 14){
            probabilidades_operadores[0].push_back(stoi(argv[i]));
        }
        else if (i >= 15 && i <= 19){
            probabilidades_operadores[1].push_back(stoi(argv[i]));
        }
        else if (i >= 20 && i <= 24){
            probabilidades_operadores[2].push_back(stoi(argv[i]));
        }
    }

    // normalizando probabilidades
    for (int i = 0; i < probabilidades_operadores.size(); i++){
        int suma = 0;
        for (int j = 0; j < probabilidades_operadores[i].size(); j++){
            suma += probabilidades_operadores[i][j];
        }
        for (int j = 0; j < probabilidades_operadores[i].size(); j++){
            probabilidades_operadores[i][j] = int(probabilidades_operadores[i][j]*100/suma);
        }
    }

    //imprimiendo parametros
    /*
    cout << "Nombre archivo: " << nombre_archivo << endl;

    cout << "Semilla: " << semilla << endl;
    
    cout << "Iteraciones: " << iteraciones << endl;
    cout << "Largos listas equipos: ";
    for (int i = 0; i < largos_listas_equipos.size(); i++){
        cout << largos_listas_equipos[i] << " ";
    }
    cout << endl;
    cout << "Largos listas fechas: ";
    for (int i = 0; i < largos_listas_fechas.size(); i++){
        cout << largos_listas_fechas[i] << " ";
    }
    cout << endl;
    cout << "Probabilidades operadores: " << endl;
    for (int i = 0; i < probabilidades_operadores.size(); i++){
        for (int j = 0; j < probabilidades_operadores[i].size(); j++){
            cout << probabilidades_operadores[i][j] << " ";
        }
        cout << endl;
    }
    */

    // ---------------------------------------------------- lectura de instanica EPL ----------------------------------------------------

    ifstream file(nombre_archivo); 
  
    // String to store each line of the file. 
    string line; 
  
    if (file.is_open()) { 
        // Read each line from the file and store it in the 
        // 'line' variable. 
        while (getline(file, line)) { 
            //cout << line << endl;
            if (contador_fila == 0){
                cantidad_equipos = stoi(line);
                //cout << "Cantidad de equipos: " << cantidad_equipos << endl;
            }
            else if (contador_fila <= cantidad_equipos){ //distancias
                //cout << "Equipo: " << line << endl;
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                //std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
                //cout << vstrings[19] << endl;

                aux_distancias.clear();
                for (int i = 0; i < vstrings.size(); i++){
                    if (vstrings[i] == "M"){
                        aux_distancias.push_back(10000);
                    }
                    else{
                        aux_distancias.push_back(stoi(vstrings[i]));
                    }
                }
                distancias.push_back(aux_distancias);
            }
            else if (contador_fila == cantidad_equipos+1){ // equipos fuertes
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_fuertes.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+2){ // equipos UCL
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_UCL.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+3){ // equipos UEL
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_UEL.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+4){ // equipos UECL
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_UECL.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+5){ // equipos emparejados
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    equipos_emparejados.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+6){ // fechas previas FA Cup
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_previas_FA_Cup.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+7){ // fechas posteriores FA Cup
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_posteriores_FA_Cup.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+8){ // fechas previas UCL
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end); // vstrings tiene cada palabra de la linea
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_previas_UCL.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+9){ // fechas posteriores UCL
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end);
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_posteriores_UCL.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+10){ // fechas previas UEL
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end);
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_previas_UEL.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+11){ // fechas posteriores UEL
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end);
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_posteriores_UEL.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+12){ // fechas previas UECL
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end);
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_previas_UECL.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+13){ // fechas posteriores UECL
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end);
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_posteriores_UECL.push_back(stoi(vstrings[i]));
                }
            }
            else if (contador_fila == cantidad_equipos+14){ // numero solicituedes visitante
                numero_solicitudes = stoi(line);
            }
            else if(contador_fila >= cantidad_equipos+15 && contador_fila < cantidad_equipos+15 + numero_solicitudes){ //solicitudes visitante
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
            else if(contador_fila == cantidad_equipos+ 15 + numero_solicitudes){ // fechas bank holidays
                std::stringstream ss(line);
                std::istream_iterator<std::string> begin(ss);
                std::istream_iterator<std::string> end;
                std::vector<std::string> vstrings(begin, end);
                for (int i = 0; i < vstrings.size(); i++){
                    fechas_bank_holidays.push_back(stoi(vstrings[i]));
                }
            }
            else if(contador_fila == cantidad_equipos+ 16 + numero_solicitudes){ // fecha boxing day
                fecha_boxing_day = stoi(line);
            }
            else if(contador_fila == cantidad_equipos+ 17 + numero_solicitudes){ // fecha new year
                fecha_new_year = stoi(line);
            }
            else if(contador_fila == cantidad_equipos+ 18 + numero_solicitudes){ // distancia optima
                distancia_optima = stoi(line);
            }
            contador_fila++;
        } 
  
        // Close the file stream once all lines have been 
        // read. 
        file.close(); 
    } 
    else { 
        // Print an error message to the standard error 
        // stream if the file cannot be opened. 
        cout << "Unable to open file\n";
    }

    // Los premios entregados en el Conference League son similares a los de la Europa League y se disputan en las mismas fechas
    // Por este motivo, se va a incluir a los equipos de confernce en la lista de equipos que juegan la UEL para no modificar mas restricciones

    for (int i = 0; i < equipos_UECL.size(); i++){
        if (equipos_UECL[i] != 0){
            equipos_UEL.push_back(equipos_UECL[i]);
        }
    }

    // ------------------------------------------------- fin lectura de instanica EPL ---------------------------------------------------

    vector<vector<int>> rueda1_inicial = creacion_fixture_inicial(20);
    vector<vector<int>> rueda2_inicial = generacion_rueda_mirrored(rueda1_inicial);
    
    vector<vector<vector<int>>> ruedas_TS = tabu_search_epl_reducido(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_inicial, rueda2_inicial, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, fechas_bank_holidays, solicituedes_visitante, distancias, largos_listas_equipos, largos_listas_fechas, probabilidades_operadores, iteraciones, semilla);

    vector<vector<int>> rueda1_TS = ruedas_TS[0];
    vector<vector<int>> rueda2_TS = ruedas_TS[1];

    int evaluacion_actual_TS = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_TS, rueda2_TS, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, fechas_bank_holidays, solicituedes_visitante, distancias);
    int distancia_total_TS = distancia_festivos(rueda1_TS, rueda2_TS, distancias, fecha_boxing_day, fecha_new_year);

    bool info_completa = false;

    if(!info_completa){
        cout << evaluacion_actual_TS << endl;
    }
    else{ // se muetsrab todos los datos y se realiza un HC MM con la solucion final

        //imprimir parametros de entrada
        /*
        cout << "Parametros de entrada" << endl;

        cout << "Iteraciones: " << iteraciones << endl;

        cout << "Largos listas equipos: ";
        for (int i = 0; i < largos_listas_equipos.size(); i++){
            cout << largos_listas_equipos[i] << " ";
        }
        cout << endl;

        cout << "Largos listas fechas: ";
        for (int i = 0; i < largos_listas_fechas.size(); i++){
            cout << largos_listas_fechas[i] << " ";
        }
        cout << endl;

        cout << "Probabilidades operadores" << endl;
        for (int i = 0; i < probabilidades_operadores.size(); i++){
            cout << "Fase " << i+1 << ": ";
            for (int j = 0; j < probabilidades_operadores[i].size(); j++){
                cout << probabilidades_operadores[i][j] << " ";
            }
            cout << endl;
        }
        */

        print_calendarizacion(rueda1_TS, rueda2_TS);
        cout << "\nFixture TS" << endl;
        cout << "Distancia total: " << distancia_total_TS << endl;
        cout << "Valor evaluacion: " << evaluacion_actual_TS << endl;
        cout << "\n";

        print_costo_restricciones_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_TS, rueda2_TS, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, fechas_bank_holidays, solicituedes_visitante, distancias);

        //cout << "Contando signos negativos por columna" << endl;

        //cout << "Rueda 1" << endl;

        for (int i = 0; i < 19; i++){
            int contador = 0;
            for (int j = 0; j < 20; j++){
                if (rueda1_TS[j][i] < 0){
                    contador++;
                }
            }
            //cout << "Fecha " << i+1 << ": " << contador << endl;
        }

        //cout << "Rueda 2" << endl;

        for (int i = 0; i < 19; i++){
            int contador = 0;
            for (int j = 0; j < 20; j++){
                if (rueda2_TS[j][i] < 0){
                    contador++;
                }
            }
            //cout << "Fecha " << i+1 << ": " << contador << endl;
        }

        int contador_errores_localias_inversas = 0;

        //revisando que las localias esten invertidas por equipos
        for (int i = 0; i < 20; i++){
            for (int j = 0; j < 19; j++){ //rueda1
                int rival_primera_rueda = abs(rueda1_TS[i][j]);
                for (int k = 0; k < 19; k++){ // rueda2
                    if (abs(rueda2_TS[i][k]) == rival_primera_rueda){
                        if (rueda1_TS[i][j] > 0 && rueda2_TS[i][k] > 0 || rueda1_TS[i][j] < 0 && rueda2_TS[i][k] < 0){
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
        for (int i = 0; i < 19; i++){ // por fecha
            suma_col = 0;
            for (int j = 0; j < 20; j++){ // por equipo
                suma_col += abs(rueda1_TS[j][i]);
            }
            if (suma_col != 210){
                cout << "Error en la suma de la fecha " << i+1 << endl;
                contador_errores_sumatoria_columna++;
            }
        }

        //rueda 2
        for (int i = 0; i < 19; i++){ // por fecha
            suma_col = 0;
            for (int j = 0; j < 20; j++){ // por equipo
                suma_col += abs(rueda2_TS[j][i]);
            }
            if (suma_col != 210){
                cout << "Error en la suma de la fecha " << i+20 << endl;
                contador_errores_sumatoria_columna++;
            }
        }

        cout << "Errores encontrados suma fecha: " << contador_errores_sumatoria_columna << endl;

        //revision de que en cada rueda un equipo se enfrente a todos los demas
        vector<int> equipos_enfrentados = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        for (int i = 0; i <20; i++){
            //rueda 1
            vector<int> rivales_aux = equipos_enfrentados;
            auto it = std::find(rivales_aux.begin(), rivales_aux.end(), i+1); 
            if (it != rivales_aux.end()) { 
                rivales_aux.erase(it); 
            }
            for(int j = 0; j < 19; j++){
                auto it2 = std::find(rivales_aux.begin(), rivales_aux.end(), abs(rueda1_TS[i][j])); 
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
            for(int j = 0; j < 19; j++){
                auto it4 = std::find(rivales_aux.begin(), rivales_aux.end(), abs(rueda2_TS[i][j])); 
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
        for (int j = 0; j < 19; j++){
            for (int i = 0; i < 20; i++){
                int rival = abs(rueda1_TS[i][j]);

                // rival debe jugar contra i+1
                if(abs(rueda1_TS[rival-1][j]) != i+1){
                    cout << "Error en consistencia de fecha " << j+1 << " entre equipos " << i+1 << " y " << rival << ", el equipo " << rival << " no enfrenta a " << i+1 << endl;
                    error_consistencia_fecha++; 
                }

                // signos deben ser contrarios    
                if (rueda1_TS[i][j] > 0 && rueda1_TS[rival-1][j] > 0 || rueda1_TS[i][j] < 0 && rueda1_TS[rival-1][j] < 0){
                    cout << "Error en consistencia de fecha " << j+1 << " entre equipos " << i+1 << " y " << rival << ", ambos tienen la misma condicion" << endl;
                    error_consistencia_fecha++;
                }
            }
        }

        //revisando rueda 2
        for (int j = 0; j < 19; j++){
            for (int i = 0; i < 20; i++){
                int rival = abs(rueda2_TS[i][j]);
                // rival debe jugar contra i+1
                if(abs(rueda2_TS[rival-1][j]) != i+1){
                    cout << "Error en consistencia de fecha " << j+20 << " entre equipos " << i+1 << " y " << rival << ", el equipo " << rival << " no enfrenta a " << i+1 << endl;
                    error_consistencia_fecha++; 
                }

                // signos deben ser contrarios    
                if (rueda2_TS[i][j] > 0 && rueda2_TS[rival-1][j] > 0 || rueda2_TS[i][j] < 0 && rueda2_TS[rival-1][j] < 0){
                    cout << "Error en consistencia de fecha " << j+20 << " entre equipos " << i+1 << " y " << rival << ", ambos tienen la misma condicion" << endl;
                    error_consistencia_fecha++;
                }
            }
        }
        
        cout << "Errores en consistencia de fecha: " << error_consistencia_fecha << endl;
        
        /*
        
        cout << "Aplicando Hill Climbing mejor mejora con solucion de TS" << endl;

        vector<vector<vector<int>>> ruedas_HCMM_TS = hill_climbing_epl_mejor_mejora(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_TS, rueda2_TS, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, fechas_bank_holidays, solicituedes_visitante, distancias);

        int evaluacion_actual_HCMM_TS = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, ruedas_HCMM_TS[0], ruedas_HCMM_TS[1], equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, fechas_bank_holidays, solicituedes_visitante, distancias);
        int distancia_total_HCMM_TS = distancia_festivos(ruedas_HCMM_TS[0], ruedas_HCMM_TS[1], distancias, fecha_boxing_day, fecha_new_year);

        cout << "\nFixture HCMM_TS" << endl;
        cout << "Distancia total: " << distancia_total_HCMM_TS << endl;
        cout << "Valor evaluacion: " << evaluacion_actual_HCMM_TS << endl;
        cout << "\n";

        print_calendarizacion(ruedas_HCMM_TS[0], ruedas_HCMM_TS[1]);

        print_costo_restricciones_epl(distancia_optima, fecha_boxing_day, fecha_new_year, ruedas_HCMM_TS[0], ruedas_HCMM_TS[1], equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, fechas_bank_holidays, solicituedes_visitante, distancias);
        

        rueda1_TS = ruedas_HCMM_TS[0];
        rueda2_TS = ruedas_HCMM_TS[1];

        cout << "Contando signos negativos por columna" << endl;

        cout << "Rueda 1" << endl;

        for (int i = 0; i < 19; i++){
            int contador = 0;
            for (int j = 0; j < 20; j++){
                if (rueda1_TS[j][i] < 0){
                    contador++;
                }
            }
            cout << "Fecha " << i+1 << ": " << contador << endl;
        }

        cout << "Rueda 2" << endl;

        for (int i = 0; i < 19; i++){
            int contador = 0;
            for (int j = 0; j < 20; j++){
                if (rueda2_TS[j][i] < 0){
                    contador++;
                }
            }
            cout << "Fecha " << i+1 << ": " << contador << endl;
        }

        contador_errores_localias_inversas = 0;

        //revisando que las localias esten invertidas por equipos
        for (int i = 0; i < 20; i++){
            for (int j = 0; j < 19; j++){ //rueda1
                int rival_primera_rueda = abs(rueda1_TS[i][j]);
                for (int k = 0; k < 19; k++){ // rueda2
                    if (abs(rueda2_TS[i][k]) == rival_primera_rueda){
                        if (rueda1_TS[i][j] > 0 && rueda2_TS[i][k] > 0 || rueda1_TS[i][j] < 0 && rueda2_TS[i][k] < 0){
                            cout << "Error en localias inversas equipos " << i+1 << " y " << rival_primera_rueda << endl;
                            contador_errores_localias_inversas++;
                        }
                    }
                }
            }
        }

        cout << "Errores encontrados: " << contador_errores_localias_inversas << endl;

        contador_errores_sumatoria_columna = 0;

        //rueda 1
        for (int i = 0; i < 19; i++){ // por fecha
            suma_col = 0;
            for (int j = 0; j < 20; j++){ // por equipo
                suma_col += abs(rueda1_TS[j][i]);
            }
            if (suma_col != 210){
                cout << "Error en la suma de la fecha " << i+1 << endl;
                contador_errores_sumatoria_columna++;
            }
        }

        //rueda 2
        for (int i = 0; i < 19; i++){ // por fecha
            suma_col = 0;
            for (int j = 0; j < 20; j++){ // por equipo
                suma_col += abs(rueda2_TS[j][i]);
            }
            if (suma_col != 210){
                cout << "Error en la suma de la fecha " << i+20 << endl;
                contador_errores_sumatoria_columna++;
            }
        }

        cout << "Errores encontrados suma fecha: " << contador_errores_sumatoria_columna << endl;

        //revision de que en cada rueda un equipo se enfrente a todos los demas
        equipos_enfrentados = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        for (int i = 0; i <20; i++){
            //rueda 1
            vector<int> rivales_aux = equipos_enfrentados;
            auto it = std::find(rivales_aux.begin(), rivales_aux.end(), i+1); 
            if (it != rivales_aux.end()) { 
                rivales_aux.erase(it); 
            }
            for(int j = 0; j < 19; j++){
                auto it2 = std::find(rivales_aux.begin(), rivales_aux.end(), abs(rueda1_TS[i][j])); 
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
            for(int j = 0; j < 19; j++){
                auto it4 = std::find(rivales_aux.begin(), rivales_aux.end(), abs(rueda2_TS[i][j])); 
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

        error_consistencia_fecha = 0;

        //revisando rueda 1
        for (int j = 0; j < 19; j++){
            for (int i = 0; i < 20; i++){
                int rival = abs(rueda1_TS[i][j]);

                // rival debe jugar contra i+1
                if(abs(rueda1_TS[rival-1][j]) != i+1){
                    cout << "Error en consistencia de fecha " << j+1 << " entre equipos " << i+1 << " y " << rival << ", el equipo " << rival << " no enfrenta a " << i+1 << endl;
                    error_consistencia_fecha++; 
                }

                // signos deben ser contrarios    
                if (rueda1_TS[i][j] > 0 && rueda1_TS[rival-1][j] > 0 || rueda1_TS[i][j] < 0 && rueda1_TS[rival-1][j] < 0){
                    cout << "Error en consistencia de fecha " << j+1 << " entre equipos " << i+1 << " y " << rival << ", ambos tienen la misma condicion" << endl;
                    error_consistencia_fecha++;
                }
            }
        }

        //revisando rueda 2
        for (int j = 0; j < 19; j++){
            for (int i = 0; i < 20; i++){
                int rival = abs(rueda2_TS[i][j]);
                // rival debe jugar contra i+1
                if(abs(rueda2_TS[rival-1][j]) != i+1){
                    cout << "Error en consistencia de fecha " << j+20 << " entre equipos " << i+1 << " y " << rival << ", el equipo " << rival << " no enfrenta a " << i+1 << endl;
                    error_consistencia_fecha++; 
                }

                // signos deben ser contrarios    
                if (rueda2_TS[i][j] > 0 && rueda2_TS[rival-1][j] > 0 || rueda2_TS[i][j] < 0 && rueda2_TS[rival-1][j] < 0){
                    cout << "Error en consistencia de fecha " << j+20 << " entre equipos " << i+1 << " y " << rival << ", ambos tienen la misma condicion" << endl;
                    error_consistencia_fecha++;
                }
            }
        }
        
        cout << "Errores en consistencia de fecha: " << error_consistencia_fecha << endl;
        */
    }

    return 0;
} 