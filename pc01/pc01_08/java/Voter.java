/**
 * Australian voting
 * pc110108
 * uva10142
 */

class Voter {
    int[] preferences;
    int currentPreference;
    
    public Voter(int numCandidates) {
        preferences = new int[numCandidates];
        currentPreference = 0;
    }
}