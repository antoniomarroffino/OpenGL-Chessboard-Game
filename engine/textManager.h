/**
 * @file    textManager.h
 * @brief   Manager per la visualizzazione del testo.
 *
 * Questo file contiene la classe `TextManager` che si occupa della gestione e visualizzazione del testo
 * sulla finestra grafica. La classe può visualizzare una lista di stringhe e i frame per secondo (FPS) in un
 * contesto 3D, utilizzando un'ortho camera (una proiezione ortogonale) per il rendering.
 *
 * @authors Luca Fantò (C) SUPSI [luca.fanto@student.supsi.ch]
 *          Mattia Cainarca (C) SUPSI [mattia.cainarca@student.supsi.ch]
 *          Antonio Marroffino (C) SUPSI [antonio.marroffino@student.supsi.ch]
 */

#pragma once

 //////////////
 // #INCLUDE //
 //////////////

// Standard libraries
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

// Project-specific includes
#include "orthoCamera.h"

 /**
  * @brief Classe per la gestione della visualizzazione del testo.
  *
  * La classe `TextManager` si occupa di visualizzare testo sulla finestra grafica, utilizzando una
  * `Camera` ortogonale per la proiezione. Supporta la visualizzazione di una lista di stringhe
  * e dei frame per secondo (FPS).
  */
class ENG_API TextManager {
public:
    /**
     * @brief Costruttore di copia cancellato per evitare copie non necessarie.
     */
    TextManager(const TextManager&) = delete;

    /**
     * @brief Operatore di assegnazione cancellato per evitare assegnamenti non necessari.
     */
    TextManager& operator=(const TextManager&) = delete;

    /**
     * @brief Distruttore di default.
     */
    ~TextManager() = default;

    /**
     * @brief Restituisce l'istanza singleton della classe `TextManager`.
     *
     * Questa funzione fornisce l'accesso alla singola istanza della classe, utilizzando il pattern Singleton.
     *
     * @return L'istanza singleton della classe `TextManager`.
     */
    static TextManager& getInstance();

    /**
     * @brief Visualizza una lista di testi sulla finestra.
     *
     * Questo metodo utilizza la proiezione ortogonale per rendere il testo visibile nella finestra grafica.
     * Ogni stringa viene visualizzata a partire dalla posizione verticale definita, incrementando la posizione
     * verticale per ogni riga di testo.
     *
     * @param texts La lista di stringhe da visualizzare.
     * @param orthoCamera La camera ortogonale da utilizzare per la proiezione.
     */
    void displayText(const std::list<std::string>& texts, Camera* orthoCamera) const;

    /**
     * @brief Visualizza i frame per secondo (FPS) sulla finestra.
     *
     * Questo metodo visualizza il valore degli FPS nella finestra, posizionandolo nella parte inferiore della finestra.
     *
     * @param fps Il valore degli FPS da visualizzare.
     * @param orthoCamera La camera ortogonale da utilizzare per la proiezione.
     */
    void displayFPS(const float& fps, Camera* orthoCamera) const;

private:
    /**
     * @brief Costruttore di default.
     */
    TextManager();

    /**
     * @brief Calcola la larghezza dinamica per il rendering del testo.
     *
     * Calcola la larghezza massima della lista di stringhe in base alla lunghezza della stringa più lunga.
     *
     * @param texts La lista di stringhe da cui calcolare la larghezza.
     * @return La larghezza massima calcolata.
     */
    float setDynamicWidth(const std::list<std::string>& texts) const;
};

