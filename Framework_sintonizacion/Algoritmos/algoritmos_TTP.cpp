#include <random>
#include "funcion_evaluacion.cpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

// ------------------------------------------------------------ Algoritmos Premier League ------------------------------------------------------------

vector<vector<vector<int>>> tabu_search_epl(int distancia_optima, int fecha_boxing_day, int fecha_new_year, vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_fuertes, vector<int> equipos_UCL, vector<int> equipos_UEL,
    vector<int> equipos_UECL, vector<int> equipos_emparejados, vector <int >fechas_previas_FA_Cup, vector<int> fechas_posteriores_FA_Cup, vector<int> fechas_previas_UCL,
    vector<int> fechas_posteriores_UCL, vector<int> fechas_previas_UEL, vector<int> fechas_posteriores_UEL, vector<int> fechas_previas_UECL, vector<int> fechas_posteriores_UECL, vector<int> fechas_bank_holidays, 
    vector<vector<int>> solicituedes_visitante, vector<vector<int>> distancias, vector<int> largo_lista_equipos, vector<int> largo_lista_fechas, vector<vector<int>> probabilidades_operadores, int cantidad_iteraciones_TS){

    int mejoras_totales;

    vector<vector<int>> mejor_rueda1_global, mejor_rueda2_global, rueda1_actual, rueda2_actual, rueda1_aux, rueda2_aux,mejor_rueda1_iteracion, mejor_rueda2_iteracion;

    int evaluacion_actual = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1, rueda2, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                        fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                        fechas_bank_holidays, solicituedes_visitante, distancias);

    // para contar operadores
    int Swap_homes_contador = 0;
    int Swap_teams_contador = 0;
    int Swap_rounds_contador = 0;
    int Swap_matches_contador = 0;
    int Swap_match_round_contador = 0;

    int cantidad_equipos = rueda1.size();
    int cantidad_fechas = rueda1[0].size();

    random_device rd;
    uniform_int_distribution<int> distrib_operador(1, 5);
    uniform_int_distribution<int> distrib_equipo(1, 20);
    uniform_int_distribution<int> distrib_fecha(1, 19);
    uniform_int_distribution<int> distrib_rueda(1, 2);

    uniform_int_distribution<int> distrib_probabilidad(1, 100);
    int probabilidad_operador;

    int cambio_probabilidades = cantidad_iteraciones_TS/3;

    vector<vector<vector<int>>> ruedas_reparadas;

    mejor_rueda1_global = rueda1;
    mejor_rueda2_global = rueda2;
    rueda1_actual = rueda1;
    rueda2_actual = rueda2;

    int mejor_evaluacion_gobal = evaluacion_actual;
    int nueva_evaluacion;

    int largo_lista_equipos_actual = largo_lista_equipos[0];
    int largo_lista_fechas_actual = largo_lista_fechas[0];

    vector<int> lista_tabu_equipos;
    vector<int> lista_tabu_fechas;

    // el orden de las probabilidades es SwapHomes, SwapTeams, SwapRounds, SwapMatch y SwapMatchRound
    vector<int> probabilidades_operadores_actual = probabilidades_operadores[0];

    //int operador_actual;

    int equipo1_seleccionado, equipo2_seleccionado, fecha1_seleccionada, fecha2_seleccionada, rueda_seleccionada, fecha_random_real,fecha1_real_seleccionada,fecha2_real_seleccionada;

    for(int iter=0; iter < cantidad_iteraciones_TS; iter++){


        probabilidad_operador = distrib_probabilidad(rd);

        int mejor_evaluacion_iteracion = 1000000;

        if(probabilidad_operador<probabilidades_operadores_actual[0]){ //SwapHomes

            Swap_homes_contador++;
            //cout << "SwapHomes" << endl; 

            for (int i = 1; i <= 20; i++){
                for (int j = i+1; j<=20; j++){

                    if (!is_in_vector(lista_tabu_equipos, i) && !is_in_vector(lista_tabu_equipos, j)){ // ninguno de los dos equipos no deben estar en la lista

                        rueda1_aux = SwapHomes(rueda1_actual, i, j);
                        rueda2_aux = SwapHomes(rueda2_actual, i, j);

                        nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                        fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                        fechas_bank_holidays, solicituedes_visitante, distancias);

                        if (nueva_evaluacion < mejor_evaluacion_iteracion){
                            mejor_evaluacion_iteracion = nueva_evaluacion;
                            mejor_rueda1_iteracion = rueda1_aux;
                            mejor_rueda2_iteracion = rueda2_aux;
                            equipo1_seleccionado = i;
                            equipo2_seleccionado = j;
                        }
                    }
                }
            }
            lista_tabu_equipos.push_back(equipo1_seleccionado);
            lista_tabu_equipos.push_back(equipo2_seleccionado);

        }
        else if(probabilidad_operador < (probabilidades_operadores_actual[0] + probabilidades_operadores_actual[1])){ //SwapTeams

            Swap_teams_contador++;
            //cout << "SwapTeams" << endl;

            for (int i = 1; i <= 20; i++){
                for (int j = i+1; j<=20; j++){

                    if (!is_in_vector(lista_tabu_equipos,i) && !is_in_vector(lista_tabu_equipos,j)){


                        rueda1_aux = SwapTeams(rueda1_actual, i, j);
                        rueda2_aux = SwapTeams(rueda2_actual, i, j);
                        

                        nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                            fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                            fechas_bank_holidays, solicituedes_visitante, distancias);

                        if (nueva_evaluacion < mejor_evaluacion_iteracion){
                            mejor_evaluacion_iteracion = nueva_evaluacion;
                            mejor_rueda1_iteracion = rueda1_aux;
                            mejor_rueda2_iteracion = rueda2_aux;
                            equipo1_seleccionado = i;
                            equipo2_seleccionado = j;
                        }

                    }
                }
            }
            lista_tabu_equipos.push_back(equipo1_seleccionado);
            lista_tabu_equipos.push_back(equipo2_seleccionado);
        }
        else if(probabilidad_operador< (probabilidades_operadores_actual[0] + probabilidades_operadores_actual[1] + probabilidades_operadores_actual[2])){ //SwapRounds

            Swap_rounds_contador++;
            //cout << "SwapRounds" << endl;

            for (int i = 1; i <= 19; i++){
                for (int j = i+1; j<=19; j++){
                    for(int k = 0; k<2; k++){

                        if (k==0){
                            fecha1_real_seleccionada = i;
                            fecha2_real_seleccionada = j;
                        }
                        else{
                            fecha1_real_seleccionada = i + rueda1_actual[0].size();
                            fecha2_real_seleccionada = j + rueda1_actual[0].size();
                        }

                        if (!is_in_vector(lista_tabu_fechas, fecha1_real_seleccionada) && !is_in_vector(lista_tabu_fechas, fecha2_real_seleccionada)){ // ninguna de las dos fechas no deben estar en la lista

                            if(k==0){
                            rueda1_aux = SwapRounds(rueda1_actual, i, j);
                            rueda2_aux = rueda2_actual;
                            }
                            else{
                                rueda1_aux = rueda1_actual;
                                rueda2_aux = SwapRounds(rueda2_actual, i, j);
                            }

                            nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                            fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                            fechas_bank_holidays, solicituedes_visitante, distancias);

                            if (nueva_evaluacion < mejor_evaluacion_iteracion){
                                mejor_evaluacion_iteracion = nueva_evaluacion;
                                mejor_rueda1_iteracion = rueda1_aux;
                                mejor_rueda2_iteracion = rueda2_aux;
                                fecha1_seleccionada = fecha1_real_seleccionada;
                                fecha2_seleccionada = fecha2_real_seleccionada;
                            }
                        }
                    }
                }
            }
            lista_tabu_fechas.push_back(fecha1_seleccionada);
            lista_tabu_fechas.push_back(fecha2_seleccionada);

        }

        else if(probabilidad_operador < (probabilidades_operadores_actual[0] + probabilidades_operadores_actual[1] + probabilidades_operadores_actual[2] + probabilidades_operadores_actual[3])){ //SwapMatches (se ejecuta random 100 veces)

            Swap_matches_contador++;
            //cout << "SwapMatches" << endl;
            for(int i=1; i <= cantidad_equipos-1;i++){ //t1
                for(int j = i+1; j<= cantidad_equipos; j++){ //t1
                    for (int k = 1; k <= cantidad_fechas; k++){ //fecha
                        for(int rueda_elegida = 1; rueda_elegida <= 2; rueda_elegida++){ // rueda

                            //cout << "equipo1 " << i << " equipo2 " << j << " fecha " << k << " rueda " << rueda_elegida << endl;

                            if (rueda_elegida == 1){
                                fecha_random_real = k;
                            }
                            else{
                                fecha_random_real = k + rueda1_actual[0].size();
                            }

                            if (!is_in_vector(lista_tabu_equipos, i) && !is_in_vector(lista_tabu_equipos, j) && !is_in_vector(lista_tabu_fechas, fecha_random_real)){

                                if (rueda_elegida == 1){
                                    rueda1_aux = SwapMatches(rueda1_actual, i, j, k);

                                    ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_aux, rueda2_actual);

                                    rueda1_aux = ruedas_reparadas[0];
                                    rueda2_aux = ruedas_reparadas[1];
                                }
                                else{
                                    rueda2_aux = SwapMatches(rueda2_actual, i, j, k);

                                    ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_actual, rueda2_aux);

                                    rueda1_aux = ruedas_reparadas[0];
                                    rueda2_aux = ruedas_reparadas[1];
                                }

                                nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                                        fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                                        fechas_bank_holidays, solicituedes_visitante, distancias);

                                if (nueva_evaluacion < mejor_evaluacion_iteracion){
                                    mejor_evaluacion_iteracion = nueva_evaluacion;
                                    mejor_rueda1_iteracion = rueda1_aux;
                                    mejor_rueda2_iteracion = rueda2_aux;
                                    equipo1_seleccionado = i;
                                    equipo2_seleccionado = j;
                                    fecha1_seleccionada = k;
                                    rueda_seleccionada = rueda_elegida;
                                }
                            }
                        }
                    }
                }
            }

            lista_tabu_equipos.push_back(equipo1_seleccionado);
            lista_tabu_equipos.push_back(equipo2_seleccionado);
            if(rueda_seleccionada==1){
                lista_tabu_fechas.push_back(fecha1_seleccionada);
            }
            else{
                lista_tabu_fechas.push_back(fecha1_seleccionada+rueda1_actual[0].size());
            }
            
        }
        else if(probabilidad_operador >= (probabilidades_operadores_actual[0] + probabilidades_operadores_actual[1] + probabilidades_operadores_actual[2] + probabilidades_operadores_actual[3])){ //SwapMatchRound

            Swap_match_round_contador++;
            //cout << "SwapMatchRound" << endl;

            for(int i = 1; i<=cantidad_equipos; i++){
                for(int j = 1; j <= cantidad_fechas-1; j++){
                    for(int k = j+1; k <= cantidad_fechas; k++){
                        for(int rueda_elegida = 1; rueda_elegida <= 2; rueda_elegida++){

                            if (rueda_elegida == 1){
                                fecha1_real_seleccionada = j;
                                fecha2_real_seleccionada = k;
                            }
                            else{
                                fecha1_real_seleccionada = j + rueda1_actual[0].size();
                                fecha2_real_seleccionada = k + rueda1_actual[0].size();
                            }

                            if (!is_in_vector(lista_tabu_equipos,i) && !is_in_vector(lista_tabu_fechas, fecha1_real_seleccionada) && !is_in_vector(lista_tabu_fechas, fecha2_real_seleccionada)){
                    
                                if (rueda_elegida == 1){
                                    rueda1_aux = SwapMatchRound(rueda1_actual, i, j, k);

                                    ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_aux, rueda2_actual);

                                    rueda1_aux = ruedas_reparadas[0];
                                    rueda2_aux = ruedas_reparadas[1];
                                }
                                else{
                                    rueda2_aux = SwapMatchRound(rueda2_actual, i, j, k);

                                    ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_actual, rueda2_aux);

                                    rueda1_aux = ruedas_reparadas[0];
                                    rueda2_aux = ruedas_reparadas[1];
                                }

                                nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                                        fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                                        fechas_bank_holidays, solicituedes_visitante, distancias);

                                if (nueva_evaluacion < mejor_evaluacion_iteracion){
                                    mejor_evaluacion_iteracion = nueva_evaluacion;
                                    mejor_rueda1_iteracion = rueda1_aux;
                                    mejor_rueda2_iteracion = rueda2_aux;
                                    equipo1_seleccionado = i;
                                    fecha1_seleccionada = fecha1_real_seleccionada;
                                    fecha2_seleccionada = fecha2_real_seleccionada;
                                    rueda_seleccionada = rueda_elegida;
                                }
                            }
                        }
                    }
                }
            }

            lista_tabu_fechas.push_back(fecha1_seleccionada);
            lista_tabu_fechas.push_back(fecha2_seleccionada);
            lista_tabu_equipos.push_back(equipo1_seleccionado);
        }

        // fixture actual va a ser el mejor de la iteracion (no importa si empeora al fixture actual anterior)
        rueda1_actual = mejor_rueda1_iteracion;
        rueda2_actual = mejor_rueda2_iteracion;

        //revisando si es la mejor solucion hasta el momento
        //cout << iter << ": Mejor evaluacion iteracion: " << mejor_evaluacion_iteracion << endl;

        if (mejor_evaluacion_iteracion < mejor_evaluacion_gobal){
            mejor_evaluacion_gobal = mejor_evaluacion_iteracion;
            mejor_rueda1_global = mejor_rueda1_iteracion;
            mejor_rueda2_global = mejor_rueda2_iteracion;
            //cout << "----------------------------------------------------------- Mejora encontrada" << endl;
            mejoras_totales++;
        }
        
        // Cambiando probabilidades de los operadores
        if (iter == cambio_probabilidades){
            probabilidades_operadores_actual = probabilidades_operadores[1];
            largo_lista_equipos_actual = largo_lista_equipos[1];
            largo_lista_fechas_actual = largo_lista_fechas[1];
            //se vuelven a la mejor solucion encontrada en esa fase
            rueda1_actual = mejor_rueda1_global;
            rueda2_actual = mejor_rueda2_global;
            evaluacion_actual = mejor_evaluacion_gobal;

        }
        if (iter == 2*cambio_probabilidades){
            probabilidades_operadores_actual = probabilidades_operadores[2];
            largo_lista_equipos_actual = largo_lista_equipos[2];
            largo_lista_fechas_actual = largo_lista_fechas[2];
            //se vuelven a la mejor solucion encontrada en esa fase
            rueda1_actual = mejor_rueda1_global;
            rueda2_actual = mejor_rueda2_global;
            evaluacion_actual = mejor_evaluacion_gobal;

        }

        //VACIAR  ULTIMO ELEMENTOS DE LA LISTA SI ESTA LLENA (HAY QUE DEJARLAS CON EL TAMAÑO MAXIMO PARA LA SIGUIENTE ITERACION)
        while (lista_tabu_equipos.size() > largo_lista_equipos_actual){
            lista_tabu_equipos.erase(lista_tabu_equipos.begin());
        }
        
        while (lista_tabu_fechas.size() > largo_lista_fechas_actual){
            lista_tabu_fechas.erase(lista_tabu_fechas.begin());
        }

        //imprimiendo ambas listas tabu
        /*
        cout << "Lista tabu equipos: ";
        for (int i = 0; i < lista_tabu_equipos.size(); i++){
            cout << lista_tabu_equipos[i] << " ";
        }
        cout << endl;

        cout << "Lista tabu fechas: ";
        for (int i = 0; i < lista_tabu_fechas.size(); i++){
            cout << lista_tabu_fechas[i] << " ";
        }
        cout << endl;
        */

    }

    vector<vector<vector<int>>> ruedas;
    ruedas.push_back(mejor_rueda1_global);
    ruedas.push_back(mejor_rueda2_global);

    /*
    cout << "Fin fase 3" << endl;
    cout << "Contadores: " << Swap_homes_contador << " " << Swap_teams_contador << " " << Swap_rounds_contador << " " << Swap_matches_contador << " " << Swap_match_round_contador << endl;
    */

    //cout << "Mejoras totales: " << mejoras_totales << endl; 

    return ruedas;
}

vector<vector<vector<int>>> hill_climbing_epl_mejor_mejora(int distancia_optima, int fecha_boxing_day, int fecha_new_year, vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_fuertes, vector<int> equipos_UCL, vector<int> equipos_UEL,
    vector<int> equipos_UECL, vector<int> equipos_emparejados, vector <int >fechas_previas_FA_Cup, vector<int> fechas_posteriores_FA_Cup, vector<int> fechas_previas_UCL,
    vector<int> fechas_posteriores_UCL, vector<int> fechas_previas_UEL, vector<int> fechas_posteriores_UEL, vector<int> fechas_previas_UECL, vector<int> fechas_posteriores_UECL, vector<int> fechas_bank_holidays, 
    vector<vector<int>> solicituedes_visitante, vector<vector<int>> distancias){

    int mejor_evaluacion_global = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1, rueda2, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                    fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                    fechas_bank_holidays, solicituedes_visitante, distancias);

    vector<vector<int>> mejor_rueda1_global, mejor_rueda2_global, mejor_rueda1_iteracion, mejor_rueda2_iteracion, rueda1_aux, rueda2_aux;

    vector<vector<vector<int>>> ruedas_reparadas;

    int nueva_evaluacion;

    mejor_rueda1_global = rueda1;
    mejor_rueda2_global = rueda2;

    bool mejora = true;
    while (mejora == true){

        int mejor_evaluacion_iteracion = 1000000;

        //aplicar todos los operadores a la rueda actual y comparar con mejor evaluacion iteracion

        //todos los SwapHomes
        for (int i = 1; i <= 19; i++){
            for (int j = i+1; j<=20; j++){

                rueda1_aux = SwapHomes(mejor_rueda1_global, i, j);
                rueda2_aux = SwapHomes(mejor_rueda2_global, i, j);

                nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                fechas_bank_holidays, solicituedes_visitante, distancias);

                if (nueva_evaluacion < mejor_evaluacion_iteracion){
                    mejor_evaluacion_iteracion = nueva_evaluacion;
                    mejor_rueda1_iteracion = rueda1_aux;
                    mejor_rueda2_iteracion = rueda2_aux;
                }
            }
        }

        //todos los SwapTeams
        for (int i = 1; i <= 19; i++){
            for (int j = i+1; j<=20; j++){

                rueda1_aux = SwapTeams(mejor_rueda1_global, i, j);
                rueda2_aux = SwapTeams(mejor_rueda2_global, i, j);
                
                nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                    fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                    fechas_bank_holidays, solicituedes_visitante, distancias);

                if (nueva_evaluacion < mejor_evaluacion_iteracion){
                    mejor_evaluacion_iteracion = nueva_evaluacion;
                    mejor_rueda1_iteracion = rueda1_aux;
                    mejor_rueda2_iteracion = rueda2_aux;
                }
            }
        }

        //todos los SwapRounds
        for (int i = 1; i <= 18; i++){
            for (int j = i+1; j<=19; j++){
                for(int k = 0; k<2; k++){

                    if(k==0){
                        rueda1_aux = SwapRounds(mejor_rueda1_global, i, j);
                        rueda2_aux = mejor_rueda2_global;
                    }
                    else{
                        rueda1_aux = mejor_rueda1_global;
                        rueda2_aux = SwapRounds(mejor_rueda2_global, i, j);
                    }

                    nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                    fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                    fechas_bank_holidays, solicituedes_visitante, distancias);

                    if (nueva_evaluacion < mejor_evaluacion_iteracion){
                        mejor_evaluacion_iteracion = nueva_evaluacion;
                        mejor_rueda1_iteracion = rueda1_aux;
                        mejor_rueda2_iteracion = rueda2_aux;
                    }
                }
            }
        }

        //todos los SwapMatches
        for(int i=1; i <= 19;i++){ //t1
            for(int j = i+1; j<= 20; j++){ //t2
                for (int k = 1; k <= 19; k++){ //fecha
                    for(int rueda_elegida = 1; rueda_elegida <= 2; rueda_elegida++){ // rueda

                        //cout << "SwapMatches equipo1:" << i << " equipo 2 " << j << " fecha: " << k << " rueda " << rueda_elegida << endl;

                        if (rueda_elegida == 1){
                            rueda1_aux = SwapMatches(mejor_rueda1_global, i, j, k);

                            ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_aux, mejor_rueda2_global);

                            rueda1_aux = ruedas_reparadas[0];
                            rueda2_aux = ruedas_reparadas[1];
                        }
                        else{
                            rueda2_aux = SwapMatches(mejor_rueda2_global, i, j, k);

                            ruedas_reparadas = reparacion_ambas_ruedas_v2(mejor_rueda1_global, rueda2_aux);

                            rueda1_aux = ruedas_reparadas[0];
                            rueda2_aux = ruedas_reparadas[1];
                        }

                        nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                                fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                                fechas_bank_holidays, solicituedes_visitante, distancias);

                        if (nueva_evaluacion < mejor_evaluacion_iteracion){
                            mejor_evaluacion_iteracion = nueva_evaluacion;
                            mejor_rueda1_iteracion = rueda1_aux;
                            mejor_rueda2_iteracion = rueda2_aux;
                        }
                    }
                }
            }
        }

        //todos los SwapMatchRound
        for(int i = 1; i<=19; i++){
            for(int j = 1; j <= 20; j++){
                for(int k = j+1; k <= 19; k++){
                    for(int rueda_elegida = 1; rueda_elegida <= 2; rueda_elegida++){
                
                        if (rueda_elegida == 1){
                            rueda1_aux = SwapMatchRound(mejor_rueda1_global, i, j, k);

                            ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_aux, mejor_rueda2_global);

                            rueda1_aux = ruedas_reparadas[0];
                            rueda2_aux = ruedas_reparadas[1];
                        }
                        else{
                            rueda2_aux = SwapMatchRound(mejor_rueda2_global, i, j, k);

                            ruedas_reparadas = reparacion_ambas_ruedas_v2(mejor_rueda1_global, rueda2_aux);

                            rueda1_aux = ruedas_reparadas[0];
                            rueda2_aux = ruedas_reparadas[1];
                        }

                        nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                                fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                                fechas_bank_holidays, solicituedes_visitante, distancias);

                        if (nueva_evaluacion < mejor_evaluacion_iteracion){
                            mejor_evaluacion_iteracion = nueva_evaluacion;
                            mejor_rueda1_iteracion = rueda1_aux;
                            mejor_rueda2_iteracion = rueda2_aux;
                        }
                    }
                }
            }
        }

        //revisar si hubo mejora

        if (mejor_evaluacion_iteracion < mejor_evaluacion_global){
            mejor_rueda1_global = mejor_rueda1_iteracion;
            mejor_rueda2_global = mejor_rueda2_iteracion;
            mejor_evaluacion_global = mejor_evaluacion_iteracion;
            cout << "Mejora encontrada HCMM" << endl;
        }
        else{
            mejora = false;
        }
    }

    vector<vector<vector<int>>> ruedas;

    ruedas.push_back(mejor_rueda1_global);
    ruedas.push_back(mejor_rueda2_global);

    return ruedas;
}

vector<vector<vector<int>>> sa_epl(int distancia_optima, int fecha_boxing_day, int fecha_new_year, vector<vector<int>> rueda1, vector<vector<int>> rueda2, vector<int> equipos_fuertes, vector<int> equipos_UCL, vector<int> equipos_UEL,
    vector<int> equipos_UECL, vector<int> equipos_emparejados, vector <int >fechas_previas_FA_Cup, vector<int> fechas_posteriores_FA_Cup, vector<int> fechas_previas_UCL,
    vector<int> fechas_posteriores_UCL, vector<int> fechas_previas_UEL, vector<int> fechas_posteriores_UEL, vector<int> fechas_previas_UECL, vector<int> fechas_posteriores_UECL, vector<int> fechas_bank_holidays, 
    vector<vector<int>> solicituedes_visitante, vector<vector<int>> distancias, int temperatura_inicial, int numero_iteraciones, float tasa_cambio_temperatura, int numero_cambios_temperatura){

    int mejor_evaluacion_global = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1, rueda2, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                    fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                    fechas_bank_holidays, solicituedes_visitante, distancias);

    vector<vector<int>> mejor_rueda1_global, mejor_rueda2_global, rueda1_actual, rueda2_actual, rueda1_aux, rueda2_aux, mejor_rueda1_iteracion, mejor_rueda2_iteracion;

    vector<vector<vector<int>>> ruedas_reparadas;

    int nueva_evaluacion;

    mejor_rueda1_global = rueda1;
    mejor_rueda2_global = rueda2;

    rueda1_actual = rueda1;
    rueda2_actual = rueda2;
    int mejor_evaluacion_actual = mejor_evaluacion_global;

    int temperatura = temperatura_inicial;
    int cantidad_iteraciones = numero_iteraciones;
    float cambio_temperatura = tasa_cambio_temperatura;
    int cantidad_cambios_temperatura = numero_cambios_temperatura; 
    int iteraciones_para_cambio = cantidad_iteraciones/cantidad_cambios_temperatura;

    int evaluacion_actual = mejor_evaluacion_global;
    rueda1_actual = mejor_rueda1_global;
    rueda2_actual = mejor_rueda2_global;

    random_device rd;
    uniform_int_distribution<int> distrib_operador(1, 5);
    uniform_int_distribution<int> distrib_equipo(1, 20);
    uniform_int_distribution<int> distrib_fecha(1, 19);
    uniform_int_distribution<int> distrib_rueda(1, 2);

    int equipo1_seleccionado, equipo2_seleccionado, fecha1_seleccionada, fecha2_seleccionada, rueda_seleccionada, fecha_random_real,fecha1_real_seleccionada,fecha2_real_seleccionada;

    int contador_iteraciones_cambio_temperatura = 0;

    for (int iteracion=0; iteracion < cantidad_iteraciones; iteracion++){
        int operador = distrib_operador(rd);

        int mejor_evaluacion_iteracion = 999999;

        if(operador == 1){ // SWAP HOMES
            
            for (int iter_sh = 0; iter_sh < 95; iter_sh++){ // vecindario completo 190

                int equipo_1 = distrib_equipo(rd);
                int equipo_2 = distrib_equipo(rd);

                while (equipo_1 == equipo_2){
                    equipo_2 = distrib_equipo(rd);
                }

                rueda1_aux = SwapHomes(rueda1_actual, equipo_1, equipo_2);
                rueda2_aux = SwapHomes(rueda2_actual, equipo_1, equipo_2);

                nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                fechas_bank_holidays, solicituedes_visitante, distancias);

                if (nueva_evaluacion < mejor_evaluacion_iteracion){
                    mejor_evaluacion_iteracion = nueva_evaluacion;
                    mejor_rueda1_iteracion = rueda1_aux;
                    mejor_rueda2_iteracion = rueda2_aux;
                }
            }
            
        }
        else if (operador == 2){ // SWAP TEAMS
            
                for (int iter_sr = 0; iter_sr < 190; iter_sr++){ // vecindario completo 190

                    int equipo_1 = distrib_equipo(rd);
                    int equipo_2 = distrib_equipo(rd);

                    while (equipo_1 == equipo_2){
                        equipo_2 = distrib_equipo(rd);
                    }

                    rueda1_aux = SwapTeams(rueda1_actual, equipo_1, equipo_2);
                    rueda2_aux = SwapTeams(rueda2_actual, equipo_1, equipo_2);
                    
                    nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                        fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                        fechas_bank_holidays, solicituedes_visitante, distancias);

                    if (nueva_evaluacion < mejor_evaluacion_iteracion){
                        mejor_evaluacion_iteracion = nueva_evaluacion;
                        mejor_rueda1_iteracion = rueda1_aux;
                        mejor_rueda2_iteracion = rueda2_aux;
                    }
                }
            
        }
        else if (operador == 3){ // SWAP ROUNDS
            
            for(int k = 0; k<171; k++){ // vecindario completo 342

                int fecha_1 = distrib_fecha(rd);
                int fecha_2 = distrib_fecha(rd);
                int rueda_seleccionada = distrib_rueda(rd);

                if(rueda_seleccionada==1){
                    rueda1_aux = SwapRounds(rueda1_actual, fecha_1, fecha_2);
                    rueda2_aux = rueda2_actual;
                }
                else{
                    rueda1_aux = rueda1_actual;
                    rueda2_aux = SwapRounds(rueda2_actual, fecha_1, fecha_2);
                }

                nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                fechas_bank_holidays, solicituedes_visitante, distancias);

                if (nueva_evaluacion < mejor_evaluacion_iteracion){
                    mejor_evaluacion_iteracion = nueva_evaluacion;
                    mejor_rueda1_iteracion = rueda1_aux;
                    mejor_rueda2_iteracion = rueda2_aux;
                }
            }
        }
        else if (operador == 4){ // SWAP MATCHES

            for(int iter_sm = 1; iter_sm <= 3860; iter_sm++){ // vecindario completo 7720

                int equipo_1 = distrib_equipo(rd);
                int equipo_2 = distrib_equipo(rd);
                int fecha_seleccionada = distrib_fecha(rd);
                int rueda_elegida = distrib_rueda(rd);

                //cout << "SwapMatches equipo1:" << i << " equipo 2 " << j << " fecha: " << k << " rueda " << rueda_elegida << endl;

                if (rueda_elegida == 1){
                    rueda1_aux = SwapMatches(rueda1_actual, equipo_1, equipo_2, fecha_seleccionada);

                    ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_aux, rueda2_actual);

                    rueda1_aux = ruedas_reparadas[0];
                    rueda2_aux = ruedas_reparadas[1];
                }
                else{
                    rueda2_aux = SwapMatches(rueda2_actual, equipo_1, equipo_2, fecha_seleccionada);

                    ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_actual, rueda2_aux);

                    rueda1_aux = ruedas_reparadas[0];
                    rueda2_aux = ruedas_reparadas[1];
                }

                nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                        fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                        fechas_bank_holidays, solicituedes_visitante, distancias);

                if (nueva_evaluacion < mejor_evaluacion_iteracion){
                    mejor_evaluacion_iteracion = nueva_evaluacion;
                    mejor_rueda1_iteracion = rueda1_aux;
                    mejor_rueda2_iteracion = rueda2_aux;
                }
            }   
        }
        else{

            for(int iter_smr = 1; iter_smr <= 3420; iter_smr++){ //vecindario completo 6840

                int equipo_1 = distrib_equipo(rd);
                int fecha_1 = distrib_fecha(rd);
                int fecha_2 = distrib_fecha(rd);
                int rueda_elegida = distrib_rueda(rd);
        
                if (rueda_elegida == 1){
                    rueda1_aux = SwapMatchRound(rueda1_actual, equipo_1, fecha_1, fecha_2);

                    ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_aux, rueda2_actual);

                    rueda1_aux = ruedas_reparadas[0];
                    rueda2_aux = ruedas_reparadas[1];
                }
                else{
                    rueda2_aux = SwapMatchRound(rueda2_actual, equipo_1, fecha_1, fecha_2);

                    ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_actual, rueda2_aux);

                    rueda1_aux = ruedas_reparadas[0];
                    rueda2_aux = ruedas_reparadas[1];
                }

                nueva_evaluacion = funcion_evaluacion_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                        fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                        fechas_bank_holidays, solicituedes_visitante, distancias);

                if (nueva_evaluacion < mejor_evaluacion_iteracion){
                    mejor_evaluacion_iteracion = nueva_evaluacion;
                    mejor_rueda1_iteracion = rueda1_aux;
                    mejor_rueda2_iteracion = rueda2_aux;
                }
            }
            
        }

        if (mejor_evaluacion_iteracion <= mejor_evaluacion_actual){
            mejor_evaluacion_actual = mejor_evaluacion_iteracion;
            rueda1_actual = mejor_rueda1_iteracion;
            rueda2_actual = mejor_rueda2_iteracion;

            //cout << "Mejora encontrada en la iteracion " << iteracion << endl;

            //cout << "Mejor evaluacion actual: " << mejor_evaluacion_actual << " Mejor evaluacion iteracion: " << mejor_evaluacion_iteracion << " Temperatura: " << temperatura << endl;

            if (mejor_evaluacion_iteracion < mejor_evaluacion_global){
                mejor_evaluacion_global = mejor_evaluacion_iteracion;
                mejor_rueda1_global = mejor_rueda1_iteracion;
                mejor_rueda2_global = mejor_rueda2_iteracion;

                //cout << "-------------------------------------------- Mejora global encontrada en la iteracion " << iteracion << "Nuevo optimo global" << mejor_evaluacion_global << endl;
            }
        }
        else{

            float delta = mejor_evaluacion_iteracion - mejor_evaluacion_actual;

            float delta_T = delta/temperatura * -1;

            float probabilidad_aceptacion = exp(delta_T);

            //cout << "Mejor evaluacion actual: " << mejor_evaluacion_actual << " Mejor evaluacion iteracion: " << mejor_evaluacion_iteracion << " Temperatura: " << temperatura << endl;

            uniform_real_distribution<float> distrib_probabilidad(0, 1);
            float probabilidad_aleatoria = distrib_probabilidad(rd);

            //cout << "Probabilidad de aceptacion: " << probabilidad_aceptacion << " Probabilidad aleatoria: " << probabilidad_aleatoria << endl;

            if (probabilidad_aleatoria < probabilidad_aceptacion){
                mejor_evaluacion_actual = mejor_evaluacion_iteracion;
                rueda1_actual = mejor_rueda1_iteracion;
                rueda2_actual = mejor_rueda2_iteracion;

                //cout << "Solucion peor aceptada en la iteracion " << iteracion << endl;
                //cout << "Solucion anterior: " << mejor_evaluacion_actual << endl; 

            }
            else{
                //cout << "Solucion peor rechazada en la iteracion " << iteracion << endl;
            }
        }

        //cambio de temperatura

        contador_iteraciones_cambio_temperatura++;

        if (contador_iteraciones_cambio_temperatura == iteraciones_para_cambio){
            temperatura = temperatura * cambio_temperatura;
            contador_iteraciones_cambio_temperatura = 0;
        }
    }

    vector<vector<vector<int>>> ruedas;

    ruedas.push_back(mejor_rueda1_global);
    ruedas.push_back(mejor_rueda2_global);

    return ruedas;
}

// ------------------------------------------------------------ FUNCIONES FUTBOL CHILENO ------------------------------------------------------------

vector<vector<vector<int>>> tabu_search_pdc(vector<vector<int>> rueda1, vector<vector<int>> rueda2, int fecha_limite_vacaciones, vector<int> equipos_fuertes, vector<int> equipos_libertadores, vector<int> equipos_prelibertadores, 
    vector<int> equipos_sudamericana, vector<int> equipos_zona_norte, vector<int> equipos_zona_centro, vector<int> equipos_zona_sur, vector<int> equipos_zona_vacaciones, vector<int> equipos_santiago,
    vector<int> fechas_previas_prelibertadores, vector<int> fechas_posteriores_prelibertadores, vector<int> fechas_previas_libertadores, vector<int> fechas_posteriores_libertadores, vector<int> fechas_previas_sudamericana,
    vector<int> fechas_posteriores_sudamericana, vector<vector<int>> solicituedes_visitante, vector<int> largo_listas_equipos, vector<int> largo_listas_fechas, vector<vector<int>> probabilidades_operadores_fases, int numero_iteraciones){

    int mejoras_totales;

    vector<vector<int>> mejor_rueda1_global, mejor_rueda2_global, rueda1_actual, rueda2_actual, rueda1_aux, rueda2_aux,mejor_rueda1_iteracion, mejor_rueda2_iteracion;

    int evaluacion_actual = funcion_evaluacion_pdc(rueda1, rueda2, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                            equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                            fechas_posteriores_sudamericana, solicituedes_visitante);

    // para contar operadores
    int Swap_homes_contador = 0;
    int Swap_teams_contador = 0;
    int Swap_rounds_contador = 0;
    int Swap_matches_contador = 0;
    int Swap_match_round_contador = 0;

    int cantidad_equipos = rueda1.size();
    int cantidad_fechas = rueda1[0].size();

    random_device rd;
    uniform_int_distribution<int> distrib_operador(1, 5);
    uniform_int_distribution<int> distrib_equipo(1, cantidad_equipos);
    uniform_int_distribution<int> distrib_fecha(1, cantidad_fechas);
    uniform_int_distribution<int> distrib_rueda(1, 2);

    uniform_int_distribution<int> distrib_probabilidad(1, 100);
    int probabilidad_operador;

    int cantidad_iteraciones_TS = numero_iteraciones;
    int cambio_probabilidades = cantidad_iteraciones_TS/3;

    vector<vector<vector<int>>> ruedas_reparadas;

    mejor_rueda1_global = rueda1;
    mejor_rueda2_global = rueda2;
    rueda1_actual = rueda1;
    rueda2_actual = rueda2;

    int mejor_evaluacion_gobal = evaluacion_actual;
    int nueva_evaluacion;

    int largo_lista_equipos = largo_listas_equipos[0];
    int largo_lista_fechas = largo_listas_fechas[0];

    vector<int> lista_tabu_equipos;
    vector<int> lista_tabu_fechas;

    // el orden es SwapHomes, SwapTeams, SwapRounds, SwapMatch y SwapMatchRound
    vector<int> probabilidades_operadores = probabilidades_operadores_fases[0];

    //int operador_actual;

    int equipo1_seleccionado, equipo2_seleccionado, fecha1_seleccionada, fecha2_seleccionada, rueda_seleccionada, fecha_random_real,fecha1_real_seleccionada,fecha2_real_seleccionada;

    for(int iter=0; iter < cantidad_iteraciones_TS; iter++){


        probabilidad_operador = distrib_probabilidad(rd);

        int mejor_evaluacion_iteracion = 1000000;

        if(probabilidad_operador<probabilidades_operadores[0]){ //SwapHomes

            Swap_homes_contador++;
            //cout << "SwapHomes" << endl; 

            for (int i = 1; i <= cantidad_equipos-1; i++){
                for (int j = i+1; j<=cantidad_equipos; j++){

                    if (!is_in_vector(lista_tabu_equipos, i) && !is_in_vector(lista_tabu_equipos, j)){ // ninguno de los dos equipos no deben estar en la lista

                        rueda1_aux = SwapHomes(rueda1_actual, i, j);
                        rueda2_aux = SwapHomes(rueda2_actual, i, j);

                        nueva_evaluacion = funcion_evaluacion_pdc(rueda1_aux, rueda2_aux, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                        equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                        fechas_posteriores_sudamericana, solicituedes_visitante);

                        if (nueva_evaluacion < mejor_evaluacion_iteracion){
                            mejor_evaluacion_iteracion = nueva_evaluacion;
                            mejor_rueda1_iteracion = rueda1_aux;
                            mejor_rueda2_iteracion = rueda2_aux;
                            equipo1_seleccionado = i;
                            equipo2_seleccionado = j;
                        }
                    }
                }
            }
            lista_tabu_equipos.push_back(equipo1_seleccionado);
            lista_tabu_equipos.push_back(equipo2_seleccionado);

        }
        else if(probabilidad_operador < (probabilidades_operadores[0] + probabilidades_operadores[1])){ //SwapTeams

            Swap_teams_contador++;
            //cout << "SwapTeams" << endl;

            for (int i = 1; i <= cantidad_equipos-1; i++){
                for (int j = i+1; j<=cantidad_equipos; j++){

                    if (!is_in_vector(lista_tabu_equipos,i) && !is_in_vector(lista_tabu_equipos,j)){


                        rueda1_aux = SwapTeams(rueda1_actual, i, j);
                        rueda2_aux = SwapTeams(rueda2_actual, i, j);
                        

                        nueva_evaluacion = funcion_evaluacion_pdc(rueda1_aux, rueda2_aux, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                        equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                        fechas_posteriores_sudamericana, solicituedes_visitante);

                        if (nueva_evaluacion < mejor_evaluacion_iteracion){
                            mejor_evaluacion_iteracion = nueva_evaluacion;
                            mejor_rueda1_iteracion = rueda1_aux;
                            mejor_rueda2_iteracion = rueda2_aux;
                            equipo1_seleccionado = i;
                            equipo2_seleccionado = j;
                        }

                    }
                }
            }
            lista_tabu_equipos.push_back(equipo1_seleccionado);
            lista_tabu_equipos.push_back(equipo2_seleccionado);
        }
        else if(probabilidad_operador< (probabilidades_operadores[0] + probabilidades_operadores[1] + probabilidades_operadores[2])){ //SwapRounds

            Swap_rounds_contador++;
            //cout << "SwapRounds" << endl;

            for (int i = 1; i <= cantidad_fechas-1; i++){
                for (int j = i+1; j<=cantidad_fechas; j++){
                    for(int k = 0; k<2; k++){

                        if (k==0){
                            fecha1_real_seleccionada = i;
                            fecha2_real_seleccionada = j;
                        }
                        else{
                            fecha1_real_seleccionada = i + rueda1_actual[0].size();
                            fecha2_real_seleccionada = j + rueda1_actual[0].size();
                        }

                        if (!is_in_vector(lista_tabu_fechas, fecha1_real_seleccionada) && !is_in_vector(lista_tabu_fechas, fecha2_real_seleccionada)){ // ninguna de las dos fechas no deben estar en la lista

                            if(k==0){
                            rueda1_aux = SwapRounds(rueda1_actual, i, j);
                            rueda2_aux = rueda2_actual;
                            }
                            else{
                                rueda1_aux = rueda1_actual;
                                rueda2_aux = SwapRounds(rueda2_actual, i, j);
                            }

                            nueva_evaluacion = funcion_evaluacion_pdc(rueda1_aux, rueda2_aux, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                            equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                            fechas_posteriores_sudamericana, solicituedes_visitante);

                            if (nueva_evaluacion < mejor_evaluacion_iteracion){
                                mejor_evaluacion_iteracion = nueva_evaluacion;
                                mejor_rueda1_iteracion = rueda1_aux;
                                mejor_rueda2_iteracion = rueda2_aux;
                                fecha1_seleccionada = fecha1_real_seleccionada;
                                fecha2_seleccionada = fecha2_real_seleccionada;
                            }
                        }
                    }
                }
            }
            lista_tabu_fechas.push_back(fecha1_seleccionada);
            lista_tabu_fechas.push_back(fecha2_seleccionada);

        }

        else if(probabilidad_operador < (probabilidades_operadores[0] + probabilidades_operadores[1] + probabilidades_operadores[2] + probabilidades_operadores[3])){ //SwapMatches (se ejecuta random 100 veces)

            Swap_matches_contador++;
            //cout << "SwapMatches" << endl;

            for(int i=1; i <= cantidad_equipos-1;i++){ //t1
                for(int j = i+1; j<= cantidad_equipos; j++){ //t1
                    for (int k = 1; k <= cantidad_fechas; k++){ //fecha
                        for(int rueda_elegida = 1; rueda_elegida <= 2; rueda_elegida++){ // rueda

                            if (rueda_elegida == 1){
                                fecha_random_real = k;
                            }
                            else{
                                fecha_random_real = k + rueda1_actual[0].size();
                            }

                            if (!is_in_vector(lista_tabu_equipos, i) && !is_in_vector(lista_tabu_equipos, j) && !is_in_vector(lista_tabu_fechas, fecha_random_real)){

                                if (rueda_elegida == 1){
                                    rueda1_aux = SwapMatches(rueda1_actual, i, j, k);
                                    //rueda2_aux = reparacion_rueda(rueda1_aux, rueda2_actual);

                                    ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_aux, rueda2_actual);
                                    rueda1_aux = ruedas_reparadas[0];
                                    rueda2_aux = ruedas_reparadas[1];
                                }
                                else{
                                    rueda2_aux = SwapMatches(rueda2_actual, i, j, k);
                                    //rueda1_aux = reparacion_rueda(rueda2_aux, rueda1_actual);

                                    ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_actual, rueda2_aux);
                                    rueda1_aux = ruedas_reparadas[0];
                                    rueda2_aux = ruedas_reparadas[1];
                                }

                                nueva_evaluacion = funcion_evaluacion_pdc(rueda1_aux, rueda2_aux, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                                equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                                fechas_posteriores_sudamericana, solicituedes_visitante);

                                if (nueva_evaluacion < mejor_evaluacion_iteracion){
                                    mejor_evaluacion_iteracion = nueva_evaluacion;
                                    mejor_rueda1_iteracion = rueda1_aux;
                                    mejor_rueda2_iteracion = rueda2_aux;
                                    equipo1_seleccionado = i;
                                    equipo2_seleccionado = j;
                                    fecha1_seleccionada = k;
                                    rueda_seleccionada = rueda_elegida;
                                }
                            }
                        }
                    }
                }
            }

            lista_tabu_equipos.push_back(equipo1_seleccionado);
            lista_tabu_equipos.push_back(equipo2_seleccionado);
            if(rueda_seleccionada==1){
                lista_tabu_fechas.push_back(fecha1_seleccionada);
            }
            else{
                lista_tabu_fechas.push_back(fecha1_seleccionada+rueda1_actual[0].size());
            }
        }
        else if(probabilidad_operador >= (probabilidades_operadores[0] + probabilidades_operadores[1] + probabilidades_operadores[2] + probabilidades_operadores[3])){ //SwapMatchRound

            Swap_match_round_contador++;
            //cout << "SwapMatchRound" << endl;

            for(int i = 1; i<=cantidad_equipos; i++){
                for(int j = 1; j <= cantidad_fechas-1; j++){
                    for(int k = j+1; k <= cantidad_fechas; k++){
                        for(int rueda_elegida = 1; rueda_elegida <= 2; rueda_elegida++){

                            //cout << "Equipo: " << i << " Fecha1: " << j << " Fecha2: " << k << " Rueda: " << rueda_elegida << endl;

                            if (rueda_elegida == 1){
                                fecha1_real_seleccionada = j;
                                fecha2_real_seleccionada = k;
                            }
                            else{
                                fecha1_real_seleccionada = j + rueda1_actual[0].size();
                                fecha2_real_seleccionada = k + rueda1_actual[0].size();
                            }

                            //cout << "Pre if" << endl;

                            if (!is_in_vector(lista_tabu_equipos, i) && !is_in_vector(lista_tabu_fechas, fecha1_real_seleccionada) && !is_in_vector(lista_tabu_fechas, fecha2_real_seleccionada)){

                                //cout << "Pre SwapMatchRound" << endl;
                    
                                if (rueda_elegida == 1){
                                    rueda1_aux = SwapMatchRound(rueda1_actual, i, j, k);
                                    rueda2_aux = reparacion_rueda(rueda1_aux, rueda2_actual);

                                    //ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_aux, rueda2_actual);
                                    //rueda1_aux = ruedas_reparadas[0];
                                    //rueda2_aux = ruedas_reparadas[1];
                                }
                                else{
                                    rueda2_aux = SwapMatchRound(rueda2_actual, i, j, k);
                                    rueda1_aux = reparacion_rueda(rueda2_aux, rueda1_actual);

                                    //ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_actual, rueda2_aux);
                                    //rueda1_aux = ruedas_reparadas[0];
                                    //rueda2_aux = ruedas_reparadas[1];
                                }

                                //cout << "Post SwapMatchRound" << endl;

                                nueva_evaluacion = funcion_evaluacion_pdc(rueda1_aux, rueda2_aux, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                                equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                                fechas_posteriores_sudamericana, solicituedes_visitante);

                                //cout << "Post funcion eval" << endl;

                                if (nueva_evaluacion < mejor_evaluacion_iteracion){
                                    mejor_evaluacion_iteracion = nueva_evaluacion;
                                    mejor_rueda1_iteracion = rueda1_aux;
                                    mejor_rueda2_iteracion = rueda2_aux;
                                    equipo1_seleccionado = i;
                                    fecha1_seleccionada = fecha1_real_seleccionada;
                                    fecha2_seleccionada = fecha2_real_seleccionada;
                                    rueda_seleccionada = rueda_elegida;
                                }

                                //cout << "Post asiganciones" << endl;
                            }
                        }
                    }
                }
            }

            lista_tabu_fechas.push_back(fecha1_seleccionada);
            lista_tabu_fechas.push_back(fecha2_seleccionada);
            lista_tabu_equipos.push_back(equipo1_seleccionado);
        }

        // fixture actual va a ser el mejor de la iteracion (no importa si empeora al fixture actual anterior)
        rueda1_actual = mejor_rueda1_iteracion;
        rueda2_actual = mejor_rueda2_iteracion;

        //revisando si es la mejor solucion hasta el momento
        //cout << "Mejor evaluacion iteracion: " << mejor_evaluacion_iteracion << endl;

        if (mejor_evaluacion_iteracion < mejor_evaluacion_gobal){
            mejor_evaluacion_gobal = mejor_evaluacion_iteracion;
            mejor_rueda1_global = mejor_rueda1_iteracion;
            mejor_rueda2_global = mejor_rueda2_iteracion;
            //cout << "------------------------------------ Mejora encontrada en la iteracion: " << iter << endl;
            mejoras_totales++;
        }
        
        
        // Cambiando probabilidades de los operadores
        if (iter == cambio_probabilidades){
            probabilidades_operadores = probabilidades_operadores_fases[1];
            largo_lista_equipos = largo_listas_equipos[1];
            largo_lista_fechas = largo_listas_fechas[1];
            rueda1_actual = mejor_rueda1_global;
            rueda2_actual = mejor_rueda2_global;
            evaluacion_actual = mejor_evaluacion_gobal;

        }
        if (iter == 2*cambio_probabilidades){
            probabilidades_operadores = probabilidades_operadores_fases[2];
            largo_lista_equipos = largo_listas_equipos[2];
            largo_lista_fechas = largo_listas_fechas[2];
            rueda1_actual = mejor_rueda1_global;
            rueda2_actual = mejor_rueda2_global;
            evaluacion_actual = mejor_evaluacion_gobal;

        }

        //VACIAR  ULTIMO ELEMENTOS DE LA LISTA SI ESTA LLENA (HAY QUE DEJARLAS CON EL TAMAÑO MAXIMO PARA LA SIGUIENTE ITERACION)
        while (lista_tabu_equipos.size() > largo_lista_equipos){
            lista_tabu_equipos.erase(lista_tabu_equipos.begin());
        }
        
        while (lista_tabu_fechas.size() > largo_lista_fechas){
            lista_tabu_fechas.erase(lista_tabu_fechas.begin());
        }

        //imprimiendo ambas listas tabu
        /*
        //cout << "Lista tabu equipos: ";
        for (int i = 0; i < lista_tabu_equipos.size(); i++){
            //cout << lista_tabu_equipos[i] << " ";
        }
        cout << endl;

        //cout << "Lista tabu fechas: ";
        for (int i = 0; i < lista_tabu_fechas.size(); i++){
            //cout << lista_tabu_fechas[i] << " ";
        }
        cout << endl;
        */
    }

    vector<vector<vector<int>>> ruedas;
    ruedas.push_back(mejor_rueda1_global);
    ruedas.push_back(mejor_rueda2_global);

    /*
    cout << "Fin fase 3" << endl;
    cout << "Contadores: " << Swap_homes_contador << " " << Swap_teams_contador << " " << Swap_rounds_contador << " " << Swap_matches_contador << " " << Swap_match_round_contador << endl;
    */

    //cout << "Mejoras totales: " << mejoras_totales << endl; 

    return ruedas;
}

vector<vector<vector<int>>> sa_pdc(vector<vector<int>> rueda1, vector<vector<int>> rueda2, int fecha_limite_vacaciones, vector<int> equipos_fuertes, vector<int> equipos_libertadores, vector<int> equipos_prelibertadores, 
    vector<int> equipos_sudamericana, vector<int> equipos_zona_norte, vector<int> equipos_zona_centro, vector<int> equipos_zona_sur, vector<int> equipos_zona_vacaciones, vector<int> equipos_santiago,
    vector<int> fechas_previas_prelibertadores, vector<int> fechas_posteriores_prelibertadores, vector<int> fechas_previas_libertadores, vector<int> fechas_posteriores_libertadores, vector<int> fechas_previas_sudamericana,
    vector<int> fechas_posteriores_sudamericana, vector<vector<int>> solicituedes_visitante, int temperatura_inicial, int numero_iteraciones, float tasa_cambio_temperatura, int numero_cambios_temperatura){

        int mejor_evaluacion_global = funcion_evaluacion_pdc(rueda1, rueda2, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                            equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                            fechas_posteriores_sudamericana, solicituedes_visitante);

        vector<vector<int>> mejor_rueda1_global, mejor_rueda2_global, rueda1_actual, rueda2_actual, rueda1_aux, rueda2_aux, mejor_rueda1_iteracion, mejor_rueda2_iteracion;

        vector<vector<vector<int>>> ruedas_reparadas;

        int nueva_evaluacion;

        mejor_rueda1_global = rueda1;
        mejor_rueda2_global = rueda2;

        rueda1_actual = rueda1;
        rueda2_actual = rueda2;
        int mejor_evaluacion_actual = mejor_evaluacion_global;

        int temperatura = temperatura_inicial;
        int cantidad_iteraciones = numero_iteraciones;
        float cambio_temperatura = tasa_cambio_temperatura;
        int cantidad_cambios_temperatura = numero_cambios_temperatura; 
        int iteraciones_para_cambio = cantidad_iteraciones/cantidad_cambios_temperatura;

        int evaluacion_actual = mejor_evaluacion_global;
        rueda1_actual = mejor_rueda1_global;
        rueda2_actual = mejor_rueda2_global;

        random_device rd;
        uniform_int_distribution<int> distrib_operador(1, 5);
        uniform_int_distribution<int> distrib_equipo(1, 16);
        uniform_int_distribution<int> distrib_fecha(1, 15);
        uniform_int_distribution<int> distrib_rueda(1, 2);

        int equipo1_seleccionado, equipo2_seleccionado, fecha1_seleccionada, fecha2_seleccionada, rueda_seleccionada, fecha_random_real,fecha1_real_seleccionada,fecha2_real_seleccionada;

        int contador_iteraciones_cambio_temperatura = 0;

        for (int iteracion=0; iteracion < cantidad_iteraciones; iteracion++){
            int operador = distrib_operador(rd);

            int mejor_evaluacion_iteracion = 999999;

            if(operador == 1){ // SWAP HOMES
                
                for (int iter_sh = 0; iter_sh < 60; iter_sh++){ //vecindario completo es 120

                    int equipo_1 = distrib_equipo(rd);
                    int equipo_2 = distrib_equipo(rd);

                    while (equipo_1 == equipo_2){
                        equipo_2 = distrib_equipo(rd);
                    }

                    rueda1_aux = SwapHomes(rueda1_actual, equipo_1, equipo_2);
                    rueda2_aux = SwapHomes(rueda2_actual, equipo_1, equipo_2);

                    nueva_evaluacion = funcion_evaluacion_pdc(rueda1_aux, rueda2_aux, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                            equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                            fechas_posteriores_sudamericana, solicituedes_visitante);

                    if (nueva_evaluacion < mejor_evaluacion_iteracion){
                        mejor_evaluacion_iteracion = nueva_evaluacion;
                        mejor_rueda1_iteracion = rueda1_aux;
                        mejor_rueda2_iteracion = rueda2_aux;
                    }
                }
                
            }
            else if (operador == 2){ // SWAP TEAMS
                
                    for (int iter_sr = 0; iter_sr < 60; iter_sr++){ //vecindario completo es 120

                        int equipo_1 = distrib_equipo(rd);
                        int equipo_2 = distrib_equipo(rd);

                        while (equipo_1 == equipo_2){
                            equipo_2 = distrib_equipo(rd);
                        }

                        rueda1_aux = SwapTeams(rueda1_actual, equipo_1, equipo_2);
                        rueda2_aux = SwapTeams(rueda2_actual, equipo_1, equipo_2);
                        
                        nueva_evaluacion = funcion_evaluacion_pdc(rueda1_aux, rueda2_aux, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                            equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                            fechas_posteriores_sudamericana, solicituedes_visitante);


                        if (nueva_evaluacion < mejor_evaluacion_iteracion){
                            mejor_evaluacion_iteracion = nueva_evaluacion;
                            mejor_rueda1_iteracion = rueda1_aux;
                            mejor_rueda2_iteracion = rueda2_aux;
                        }
                    }
                
            }
            else if (operador == 3){ // SWAP ROUNDS
                
                for(int k = 0; k<105; k++){ //vecindario completo es 210

                    int fecha_1 = distrib_fecha(rd);
                    int fecha_2 = distrib_fecha(rd);
                    int rueda_seleccionada = distrib_rueda(rd);

                    if(rueda_seleccionada==1){
                        rueda1_aux = SwapRounds(rueda1_actual, fecha_1, fecha_2);
                        rueda2_aux = rueda2_actual;
                    }
                    else{
                        rueda1_aux = rueda1_actual;
                        rueda2_aux = SwapRounds(rueda2_actual, fecha_1, fecha_2);
                    }

                    nueva_evaluacion = funcion_evaluacion_pdc(rueda1_aux, rueda2_aux, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                            equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                            fechas_posteriores_sudamericana, solicituedes_visitante);


                    if (nueva_evaluacion < mejor_evaluacion_iteracion){
                        mejor_evaluacion_iteracion = nueva_evaluacion;
                        mejor_rueda1_iteracion = rueda1_aux;
                        mejor_rueda2_iteracion = rueda2_aux;
                    }
                }
            }
            else if (operador == 4){ // SWAP MATCHES

                for(int iter_sm = 1; iter_sm <= 1800; iter_sm++){ // vecindario completo es 3600

                    int equipo_1 = distrib_equipo(rd);
                    int equipo_2 = distrib_equipo(rd);
                    int fecha_seleccionada = distrib_fecha(rd);
                    int rueda_elegida = distrib_rueda(rd);

                    //cout << "SwapMatches equipo1:" << i << " equipo 2 " << j << " fecha: " << k << " rueda " << rueda_elegida << endl;

                    if (rueda_elegida == 1){
                        rueda1_aux = SwapMatches(rueda1_actual, equipo_1, equipo_2, fecha_seleccionada);
                        //rueda2_aux = reparacion_rueda(rueda1_aux, rueda2_actual);

                        ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_aux, rueda2_actual);
                        //ruedas_reparadas = reparacion_ambas_ruedas_v3_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                        //            fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                        //            fechas_bank_holidays, solicituedes_visitante, distancias);
                        rueda1_aux = ruedas_reparadas[0];
                        rueda2_aux = ruedas_reparadas[1];
                    }
                    else{
                        rueda2_aux = SwapMatches(rueda2_actual, equipo_1, equipo_2, fecha_seleccionada);
                        //rueda1_aux = reparacion_rueda(rueda2_aux, rueda1_actual);

                        ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_actual, rueda2_aux);
                        //ruedas_reparadas = reparacion_ambas_ruedas_v3_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                        //            fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                        //            fechas_bank_holidays, solicituedes_visitante, distancias);
                        rueda1_aux = ruedas_reparadas[0];
                        rueda2_aux = ruedas_reparadas[1];
                    }

                    nueva_evaluacion = funcion_evaluacion_pdc(rueda1_aux, rueda2_aux, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                            equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                            fechas_posteriores_sudamericana, solicituedes_visitante);


                    if (nueva_evaluacion < mejor_evaluacion_iteracion){
                        mejor_evaluacion_iteracion = nueva_evaluacion;
                        mejor_rueda1_iteracion = rueda1_aux;
                        mejor_rueda2_iteracion = rueda2_aux;
                    }
                }
                        
                    
                
            }
            else{

                for(int iter_smr = 1; iter_smr <= 1680; iter_smr++){ // vecindario completo es 3360

                    int equipo_1 = distrib_equipo(rd);
                    int fecha_1 = distrib_fecha(rd);
                    int fecha_2 = distrib_fecha(rd);
                    int rueda_elegida = distrib_rueda(rd);
            
                    if (rueda_elegida == 1){
                        rueda1_aux = SwapMatchRound(rueda1_actual, equipo_1, fecha_1, fecha_2);
                        //rueda2_aux = reparacion_rueda(rueda1_aux, rueda2_actual);

                        ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_aux, rueda2_actual);
                        //ruedas_reparadas = reparacion_ambas_ruedas_v3_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                        //            fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                        //            fechas_bank_holidays, solicituedes_visitante, distancias);
                        rueda1_aux = ruedas_reparadas[0];
                        rueda2_aux = ruedas_reparadas[1];
                    }
                    else{
                        rueda2_aux = SwapMatchRound(rueda2_actual, equipo_1, fecha_1, fecha_2);
                        //rueda1_aux = reparacion_rueda(rueda2_aux, rueda1_actual);

                        ruedas_reparadas = reparacion_ambas_ruedas_v2(rueda1_actual, rueda2_aux);
                        //ruedas_reparadas = reparacion_ambas_ruedas_v3_epl(distancia_optima, fecha_boxing_day, fecha_new_year, rueda1_aux, rueda2_aux, equipos_fuertes, equipos_UCL, equipos_UEL, equipos_UECL, equipos_emparejados, fechas_previas_FA_Cup, 
                        //            fechas_posteriores_FA_Cup, fechas_previas_UCL, fechas_posteriores_UCL, fechas_previas_UEL, fechas_posteriores_UEL, fechas_previas_UECL, fechas_posteriores_UECL, 
                        //            fechas_bank_holidays, solicituedes_visitante, distancias);
                        rueda1_aux = ruedas_reparadas[0];
                        rueda2_aux = ruedas_reparadas[1];
                    }

                    nueva_evaluacion = funcion_evaluacion_pdc(rueda1_aux, rueda2_aux, fecha_limite_vacaciones, equipos_fuertes, equipos_libertadores, equipos_prelibertadores, equipos_sudamericana, equipos_zona_norte, equipos_zona_centro, equipos_zona_sur, 
                            equipos_zona_vacaciones, equipos_santiago, fechas_previas_prelibertadores, fechas_posteriores_prelibertadores, fechas_previas_libertadores, fechas_posteriores_libertadores, fechas_previas_sudamericana,
                            fechas_posteriores_sudamericana, solicituedes_visitante);


                    if (nueva_evaluacion < mejor_evaluacion_iteracion){
                        mejor_evaluacion_iteracion = nueva_evaluacion;
                        mejor_rueda1_iteracion = rueda1_aux;
                        mejor_rueda2_iteracion = rueda2_aux;
                    }
                }
                
            }

            if (mejor_evaluacion_iteracion <= mejor_evaluacion_actual){
                mejor_evaluacion_actual = mejor_evaluacion_iteracion;
                rueda1_actual = mejor_rueda1_iteracion;
                rueda2_actual = mejor_rueda2_iteracion;

                //cout << "Mejora encontrada en la iteracion " << iteracion << endl;

                //cout << "Mejor evaluacion actual: " << mejor_evaluacion_actual << " Mejor evaluacion iteracion: " << mejor_evaluacion_iteracion << " Temperatura: " << temperatura << endl;

                if (mejor_evaluacion_iteracion < mejor_evaluacion_global){
                    mejor_evaluacion_global = mejor_evaluacion_iteracion;
                    mejor_rueda1_global = mejor_rueda1_iteracion;
                    mejor_rueda2_global = mejor_rueda2_iteracion;

                    //cout << "-------------------------------------------- Mejora global encontrada en la iteracion " << iteracion << "Nuevo optimo global" << mejor_evaluacion_global << endl;
                }
            }
            else{

                float delta = mejor_evaluacion_iteracion - mejor_evaluacion_actual;

                float delta_T = delta/temperatura * -1;

                float probabilidad_aceptacion = exp(delta_T);

                //cout << "Mejor evaluacion actual: " << mejor_evaluacion_actual << " Mejor evaluacion iteracion: " << mejor_evaluacion_iteracion << " Temperatura: " << temperatura << endl;

                uniform_real_distribution<float> distrib_probabilidad(0, 1);
                float probabilidad_aleatoria = distrib_probabilidad(rd);

                //cout << "Probabilidad de aceptacion: " << probabilidad_aceptacion << " Probabilidad aleatoria: " << probabilidad_aleatoria << endl;

                if (probabilidad_aleatoria < probabilidad_aceptacion){
                    mejor_evaluacion_actual = mejor_evaluacion_iteracion;
                    rueda1_actual = mejor_rueda1_iteracion;
                    rueda2_actual = mejor_rueda2_iteracion;

                    //cout << "Solucion peor aceptada en la iteracion " << iteracion << endl;
                    //cout << "Solucion anterior: " << mejor_evaluacion_actual << endl; 

                }
                else{
                    //cout << "Solucion peor rechazada en la iteracion " << iteracion << endl;
                }
            }

            //cambio de temperatura

            contador_iteraciones_cambio_temperatura++;

            if (contador_iteraciones_cambio_temperatura == iteraciones_para_cambio){
                temperatura = temperatura * cambio_temperatura;
                contador_iteraciones_cambio_temperatura = 0;
            }
        }

        vector<vector<vector<int>>> ruedas;

        ruedas.push_back(mejor_rueda1_global);
        ruedas.push_back(mejor_rueda2_global);

        return ruedas;
}

