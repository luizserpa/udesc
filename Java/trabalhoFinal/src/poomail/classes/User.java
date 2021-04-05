package poomail.classes;

public class User {
    private String username;

    public User(String username) {
        this.username = username;
    }

    public void setUsername(String username){
        this.username = username;
    }

    @Override
    public String toString() {
        return this.username;
    }
}
