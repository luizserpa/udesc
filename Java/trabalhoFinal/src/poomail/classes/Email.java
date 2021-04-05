package poomail.classes;

import javafx.beans.property.SimpleStringProperty;

public class Email {
    private SimpleStringProperty emailDe = new SimpleStringProperty("");
    private SimpleStringProperty emailPara = new SimpleStringProperty("");
    private SimpleStringProperty titulo = new SimpleStringProperty("");
    private SimpleStringProperty conteudo = new SimpleStringProperty("");
    private boolean emailLido;
    private SimpleStringProperty resumo = new SimpleStringProperty("");

    public Email(String emailDe, String emailPara, String titulo, String conteudo) {
        this.emailDe.set(emailDe);
        this.emailPara.set(emailPara);
        this.titulo.set(titulo);
        this.conteudo.set(conteudo);
        this.emailLido = false;
        this.resumo.set("Titulo: " + titulo + '\n' + "De: " + emailDe);
    }

    public String getEmailDe() {
        return emailDe.get();
    }

    public SimpleStringProperty emailDeProperty() {
        return emailDe;
    }

    public String getEmailPara() {
        return emailPara.get();
    }

    public SimpleStringProperty emailParaProperty() {
        return emailPara;
    }

    public String getTitulo() {
        return titulo.get();
    }

    public SimpleStringProperty tituloProperty() {
        return titulo;
    }

    public String getConteudo() {
        return conteudo.get();
    }

    public SimpleStringProperty conteudoProperty() {
        return conteudo;
    }

    public boolean isEmailLido() {
        return emailLido;
    }

    public String getResumo() {
        return resumo.get();
    }

    public SimpleStringProperty resumoProperty() {
        return resumo;
    }

    public void emailLido(){
        this.emailLido = true;
    }

    @Override
    public String toString(){
        return "Email{" +
                "de=\"" + getEmailDe() +
                "\", para=\"" + getEmailPara() +
                "\", titulo=\"" + getTitulo() +
                "\", conteudo=\"" + getConteudo() +
                "\"}";
    }
}
