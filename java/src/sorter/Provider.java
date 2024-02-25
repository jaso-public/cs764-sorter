package sorter;

/**
 * This interface is utilized to generate records
 */
public interface Provider {
    // returns the next record or null if all desired records have been retrieved
    Record next();
}
