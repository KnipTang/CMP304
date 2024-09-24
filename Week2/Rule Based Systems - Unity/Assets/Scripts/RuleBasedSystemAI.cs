using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/**
 * RuleBasedSystemAI contains an implementation of a Rule Based System AI to control the movement of a 'Legend' automated racer
 */
public class RuleBasedSystemAI 
{

    /**
     * ruleData contains the components of each Rule 
     */
    struct ruleData
    {

        public Func<Database, bool> condition; // the rule's condition - will return true or false
        public Func<Database, int> action; // the action if the rule fires - will return a distance car moves

        public ruleData(Func<Database, bool> condition, Func<Database, int> action)
        {
            this.condition = condition;
            this.action = action;
        }

    };

    // We will use the Red playing piece for our Legend
    // This matches the information on the Legend Card
    RaceManager.LegendColours selectedLegendColour = RaceManager.LegendColours.Red; 

    // the list of all rules used by the AI
    List<ruleData> allRules = new List<ruleData>();

    public RuleBasedSystemAI()
    {
        //create our rules 
        initRules();
    }

    /**
     * initRules will create all the rules to be used by our AI and add them to the allRules object
     */
    private void initRules()
    {

        // RULE 1 - Clearing Corners
        Func<Database, bool> condition = (Database database) => {
            // Corner is closest - car is between legend line and corner
            if (database.distToNextLegendLine > database.distToNextCorner)
                return true;
            else
                return false;
        };


        Func<Database, int> action = (Database database) => {
            //TODO - implement the action for this behaivour
            // calcuate the correct move distance from the information in the Database
            return 1;
        };

        allRules.Add(new ruleData(condition, action)); 



        // RULE 2 - Approaching Corner and Speed will not take us past the corner
        Func<Database, bool> condition2 = (Database database) => {

            //TODO - complete the condition for this rule using information from the Database
            if (database.distToNextCorner > database.distToNextLegendLine)
            {
                // Legend line is closest - car is between corner and legend line, and can move at full speed without passing next corner
                return true;
            }
            else
                return false;
        };

        Func<Database, int> action2 = (Database database) => {
            //TODO - implement the action for this behaivour
            // calcuate the correct move distance from the information in the Database
            return 3;
        };

        allRules.Add(new ruleData(condition2, action2));


        // RULE 3 - Approaching Corner and but Speed will take us past the corner 
        Func<Database, bool> condition3 = (Database database) => {

            //TODO - complete the condition for this rule using information from the Database
            if (database.distToNextCorner > database.distToNextLegendLine)
            {
                // Legend line is closest - car is between corner and legend line, but moving at full speed would pass the next corner
                return true;
            }
            else
                return false;
        };

        Func<Database, int> action3 = (Database database) => {
            //TODO - implement the action for this behaivour
            // calcuate the correct move distance from the information in the Database
            return 3;   
        };

        allRules.Add(new ruleData(condition3, action3));



        /***
         *  You can add more Rules by coping the code above and editing the functions for Condition and Action
         *  Remember to add the rules to the allRules object
         */
       
        // More rules go here

    }


    /**
     * CheckRules - This function will be called each round.
     * It should create the desired AI behaviour for movement by applying Rules
     * The data needed to check the rules must be in the Database object
     * 
     */
    public int CheckRules(Database database)
    {
        // check all rules, and fire Action if the Condition returns true
        foreach (var rule in allRules)
        {
            if(rule.condition(database))
            {
                return rule.action(database); // action will return an int - the AI's move distance
            }
        }
    
        Debug.LogWarning("WARNING: No Rule Match - move distance = 0");
        return 0;
    }
}
