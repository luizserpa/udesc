package poomail.data;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class EmailData {

    private ObservableList<Email> emails;

    public EmailData() {
        this.emails = FXCollections.observableArrayList();
    }

    public ObservableList<Email> getEmails() {
        return emails;
    }

    public void addEmail(Email email){
        emails.add(email);
    }

    public void clearList(){
        if(emails != null){
            emails = FXCollections.observableArrayList();
        }
    }
}

