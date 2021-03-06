package poomail.classes;

public class Mensagem {
    String remetente;
    String destinatario;
    String assunto;
    String texto;

    public Mensagem(String remetente, String destinatario, String assunto, String texto) {
        this.remetente    = remetente;
        this.destinatario = destinatario;
        this.assunto      = assunto;
        this.texto        = texto;
    }

    public String toString() {
        String resposta = "de:" + remetente+ "\n";
        resposta += "para:" + destinatario+ "\n";
        resposta += "assunto:" + assunto+ "\n";
        resposta += "texto:" + texto+ "\n";
        return resposta;
    }

    public String getRemetente() {
        return remetente;
    }

    public String getDestinatario() {
        return destinatario;
    }

    public String getAssunto() {
        return assunto;
    }

    public String getTexto() {
        return texto;
    }
}