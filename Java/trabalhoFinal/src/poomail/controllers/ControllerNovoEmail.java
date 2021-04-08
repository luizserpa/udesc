package poomail.controllers;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import poomail.classes.*;
import poomail.data.Email;
import poomail.data.User;
import poomail.holders.EmailHolder;
import poomail.holders.UserHolder;

public class ControllerNovoEmail {

    @FXML
    private BorderPane novoEmailPage;
    @FXML
    private TextField fieldPara;
    @FXML
    private TextField fieldTitulo;
    @FXML
    private TextArea areaEmail;

    private User user;

    @FXML
    public void initialize (){
        user = UserHolder.getInstance().getUser();
        areaEmail.setWrapText(true);
    }

    @FXML
    public synchronized void enviarEmail(){
        String dest = fieldPara.getText();
        if (!dest.equals("")){
            Email novoEmail = new Email(user.toString(), dest, fieldTitulo.getText(), areaEmail.getText());
            String resposta = Talker.getInstance().enviarMensagem(
                    novoEmail.getEmailDe(),
                    novoEmail.getEmailPara(),
                    novoEmail.getTitulo(),
                    novoEmail.getConteudo());
            if (emailEnviado(resposta, novoEmail)){
                novoEmailPage.getScene().getWindow().hide();
            }else {
                alertChamado("Erro!!!");
                novoEmailPage.getScene().getWindow().hide();
            }
        }else{
            alertChamado("Campo \"Para\" Vazio");
        }
    }

    @FXML
    public void cancelarEnvio(){
        novoEmailPage.getScene().getWindow().hide();
    }

    public void alertChamado(String s){
        Alert alert = new Alert(Alert.AlertType.WARNING);
        alert.setContentText(s);
        alert.show();
    }

    public boolean emailEnviado(String resposta, Email email){
        String respostaEsperada = "{ \"okay\": { \"message\": \"mensagem enviada” } }";
        if (resposta.contains(respostaEsperada)){
            EmailHolder.getINSTANCE().setEmail(email);
            EmailHolder.getINSTANCE().setEnviado(true);
        }
        return EmailHolder.getINSTANCE().isEnviado();
    }

}
