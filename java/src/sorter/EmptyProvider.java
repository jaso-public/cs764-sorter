package sorter;

public class EmptyProvider implements Provider {

    @Override
    public Record next() {
        return null;
    }

}
