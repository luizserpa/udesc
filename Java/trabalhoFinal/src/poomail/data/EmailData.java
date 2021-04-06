package poomail.data;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class EmailData {

    private static final String DE = "de";
    private static final String PARA = "para";
    private static final String TITULO = "titulo";
    private static final String CONTEUDO = "conteudo";
    private static final String RESUMO = "resumo";

    private final ObservableList<Email> emails;

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
            for (int i = 0; i < emails.size(); i++)
                emails.remove(i);
        }
    }

}

