package poomail.holders;

import poomail.data.Email;

public class EmailHolder {
    private Email email;
    private boolean enviado;
    private final static EmailHolder INSTANCE = new EmailHolder();

    private EmailHolder(){}

    public void setEmail(Email e){
        this.email = e;
    }

    public Email getEmail() {
        return email;
    }

    public static EmailHolder getINSTANCE() {
        return INSTANCE;
    }

    public boolean isEnviado() {
        return enviado;
    }

    public void setEnviado(boolean enviado) {
        this.enviado = enviado;
    }
}
