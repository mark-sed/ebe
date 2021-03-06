/**
 * @file engine.hpp
 * @author Marek Sedlacek
 * @date August 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Engine abstraction for ebel generation
 * 
 * Constains abstractions for all ebel generation engines
 */

#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include <stddef.h>
#include <vector>
#include <utility>
#include "ir.hpp"
#include "compiler.hpp"
#include "gp.hpp"

// Forward declarations
namespace GP {
    class Population;
    class Phenotype;
}
namespace IR {
    class Node;
    class EbelNode;
    class PassWords;
    enum PassType: int;
}

/**
 * Namespace containing utilities used by the compiler that 
 * have something to do with engines.
 */ 
namespace EngineUtils {
    
    /**
     * Engine identifiers
     * This is used to identify engines without comparing string names
     */ 
    enum EngineID {
        UNKNOWN = -1,
        JENN = 0,
        MIRANDA,
        TAYLOR
    };

    /// Type holding engine ID and its corresponding name
    using TEngineInfo = std::vector<std::pair<EngineID, const char *>>;

    /// Holds all the engine IDs and names
    /// If a new engine is to be added it has to be here as well
    extern const TEngineInfo ENGINE_NAMES;

    /**
     * Returns engine ID to correspoding case-insensitive name
     * @param name Case-insensitive C string with the engine name
     * @return Engine's ID based on the passed in name
     */ 
    EngineID get_engine_id(const char *name);

    /**
     * Returns engine's name (formated)
     * @param id ID of the engine
     * @return Name of engine correspoding to the passed in id
     */ 
    const char *get_engine_name(EngineID id);
}

/**
 * Main abstract class that all engines should inherit
 */
class Engine : public Compiler {
public:
    EngineUtils::EngineID engine_id;  ///< Unique identified of the engine type
    const char *engine_name;          ///< Name of the engine (needed for info printing)
protected:
    IR::Node *text_in;        ///< IR of input example text
    IR::Node *text_out;       ///< IR of output example text
    size_t iterations;        ///< How many iterations should be done
    
    /**
     * Constructor
     * @param text_in Input IR text
     * @param text_out Output IR text
     * @param iterations Number of iterations to be done
     * @param engine_id ID of the specific engine
     */
    Engine(IR::Node *text_in, IR::Node *text_out, size_t iterations, EngineUtils::EngineID engine_id);

    /**
     * Compares 2 text IRs and returns percentage-wise similarity.
     * @param ir1 First IR to compare
     * @param ir2 Second IR to comapre
     * @return How much are ir1 and ir2 similar as a percentage (0-1)
     */ 
    float compare(IR::Node *ir1, IR::Node *ir2);
public:
    /** Destructor */
    virtual ~Engine() {}

    /**
     * Through evolution and set params generated new ebel program for input and output passed in at creation
     * @param[out] precision This value will be set to generated code's precision on provided and generated output. 
     *                       When set to nullptr should be ignored.
     * @return Ebel program generated from text_in and text_out
     */ 
    virtual IR::EbelNode *generate(float *precision) = 0;
};

struct InstructionOccurrences {
    float CONCAT;
    float DEL;
    float LOOP;
    float NOP;
    float SWAP;

    /**
     * @brief Construct a new Instruction Occurrences object
     * Uses default values for occurrences.
     * @param pass Pass type for which to generate occurrences
     */
    InstructionOccurrences(IR::PassType pass);

    friend std::ostream& operator<< (std::ostream &out, const InstructionOccurrences& occs);
};

/**
 * Struct used for configuring GP engine's evolution parameters
 */
struct GPEngineParams {
    InstructionOccurrences words_occs;///< How often should certain instructions occurre in the words pass
    InstructionOccurrences lines_occs;///< How often should certain instructions occurre in the lines pass
    size_t population_size;          ///< How many phenotypes should be in a population
    size_t min_words_pass_size;      ///< Minimal amount of instructions in one phenotype's words pass
    size_t max_words_pass_size;      ///< Maximal amount of instructions in one phenotype's words pass
    size_t min_lines_pass_size;      ///< Minimal amount of instructions in one phenotype's lines pass
    size_t max_lines_pass_size;      ///< Maximal amount of instructions in one phenotype's lines pass
    size_t pheno_min_passes;         ///< Minimal amount of passes in one phenotype
    size_t pheno_max_passes;         ///< Maximal amount of passes in one phenotype
    float init_pass_words_chance;    ///< Chance of generating words pass on init
    float init_pass_lines_chance;    ///< Chance of generating lines pass on init
    //float init_pass_document_chance;    ///< Chance of generating document pass on init
    float mutation_chance;           ///< Chance of mutation to happen
    float crossover_chance;          ///< Chance of crossover to happen
    float crossover_insert_chance;   ///< Chance for crossover to be insert type
    float crossover_switch_chance;   ///< Chance for crossover to be switch type
    bool no_crossover_when_mutated;  ///< If mutation happens then crossover cannot happen
    bool elitism;                    ///< Elitism in evolution (makes sure that best phenotype does not change)

    /**
     * @brief Construct a new GPEngineParams object
     * Parameters are set based on f_in and f_out arguments
     * @param f_in Input file for eben that works with this
     * @param f_out Output file for eben that works with this
     */
    GPEngineParams(IR::Node *f_in, IR::Node *f_out);

    friend std::ostream& operator<< (std::ostream &out, const GPEngineParams& param);
};

/**
 * Abstract class for all genetic programming engines
 */
class GPEngine : public Engine {
protected:
    GPEngineParams *params;
    GP::Population *population;
    IR::PassWords *expr_pass = nullptr;

    /**
     * Constructor
     * @param text_in Input text IR
     * @param text_out Output text IR
     * @param iterations Number of iterations to be done
     * @param engine_id ID of the specific engine
     */
    GPEngine(IR::Node *text_in, IR::Node *text_out, size_t iterations, EngineUtils::EngineID engine_id);
    virtual ~GPEngine();

    /**
     * Evaluates all the candidates and saves their fitness to fitness list
     * @param run_time_optimize If true interpreter optimizations are run over each phenotype
     * @return Returns a node with 1.0f if present otherwise nullptr
     */ 
    GP::Phenotype *evaluate(bool run_time_optimize=false);

    /**
     * Sorts population based on phenotype's fitness.
     * Sort is descending from the best fitness to the worst.
     */ 
    virtual void sort_population();

    /**
     * Mutates phenotype based on set params
     * @param pheno Phenotype to mutate
     */ 
    virtual void mutate(GP::Phenotype *pheno);
    
    /**
     * Crosses over a phenotype with other/s phenotype/s from population based on set params
     * Using insert from one phenotype to other
     * @param pheno Phenotype to be crossed over
     */ 
    virtual void crossover_insert(GP::Phenotype *pheno);

    /**
     * Crosses over a phenotype with other/s phenotype/s from population based on set params
     * Switching one section of phenotype with other
     * @param pheno Phenotype to be crossed over
     */ 
    virtual void crossover_switch(GP::Phenotype *pheno);
public:

    /* Getter and setters */
    void set_params(GPEngineParams *params) { this->params = params; }
};

#endif//_ENGINE_HPP_
