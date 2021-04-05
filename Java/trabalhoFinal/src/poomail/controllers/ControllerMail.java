package poomail.controllers;

import javafx.application.Platform;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.ObservableList;
import javafx.event.EventType;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.BorderPane;
import poomail.Main;
import poomail.classes.*;

import java.io.IOException;
import java.util.Arrays;
import java.util.EventListener;

public class ControllerMail {

    @FXML
    private BorderPane mainMailPage;
    @FXML
    private TextField fieldTitulo;
    @FXML
    private TextField fieldPara;
    @FXML
    private TextField fieldDe;
    @FXML
    private TextArea areaConteudo;
    @FXML
    private TableView<Email> tableEmails;
    @FXML
    private TableColumn tipoEntrada;
    @FXML
    private Button btnDeletar;

    private EmailData emailsCaixaEntrada;
    private EmailData emailsEnviados;
    private EmailData emailsLixeira;

    private User user;



    @FXML
    public void initialize (){
        this.emailsCaixaEntrada = new EmailData();
        this.emailsEnviados = new EmailData();
        this.emailsLixeira = new EmailData();
        this.user = UserHolder.getInstance().getUser();

        changeFocus();

        receberEmails(emailsCaixaEntrada);
        setDataTable(emailsCaixaEntrada);
    }








    @FXML
    public void novoEmail(){
        
//        try{
//            FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("scenes/novoEmail.fxml"));
//            Scene scene = mainMailPage.getScene();
//            Dialog dialog = new Dialog();
//            dialog.setTitle("Novo Email");
//            dialog.setDialogPane();
//            dialog.showAndWait();
//
//        } catch (IOException e){
//            e.printStackTrace();
//        }


    }

    @FXML
    public void tableClicked(){
        preencheEmail(tableEmails.getSelectionModel().getSelectedItem());
    }


    @FXML
    public void atualizarEmail(){
        receberEmails(emailsCaixaEntrada);
        setDataTable(emailsCaixaEntrada);
    }

    @FXML
    public void sairEmail(){
        mainMailPage.getScene().getWindow().hide();
    }

    @FXML
    public void caixaEntrada(){
        btnDeletar.setDisable(false);
        setDataTable(emailsCaixaEntrada);
    }

    @FXML
    public void enviados(){
        btnDeletar.setDisable(true);
        setDataTable(emailsEnviados);
    }

    @FXML
    public void lixeira(){
        btnDeletar.setDisable(true);
        setDataTable(emailsLixeira);
    }

    @FXML
    public void deletarEmail(){
        ObservableList<Email> data = tableEmails.getSelectionModel().getSelectedItems();
        data.forEach(e -> {
            emailsCaixaEntrada.getEmails().remove(e);
            emailsLixeira.getEmails().add(e);
        });
        setDataTable(emailsCaixaEntrada);
    }

    private void changeFocus (){
        Platform.runLater( () -> mainMailPage.requestFocus());
    }

    public void preencheEmail(Email email){
        fieldPara.setText(user.toString());
        fieldDe.setText(email.getEmailDe());
        fieldTitulo.setText(email.getTitulo());
        areaConteudo.setWrapText(true);
        areaConteudo.setText(email.getConteudo());
    }


    private void populaEmail(){
        emailsCaixaEntrada.addEmail(new Email("JM", user.toString(), "Deu ruim", "Manda o nascimento pra brasilia"));
        emailsCaixaEntrada.addEmail(new Email("LI", user.toString(), "Desconto", "Existe desconto no serviço de manicure para quem tem 9 dedos?"));
        emailsCaixaEntrada.addEmail(new Email("Eneias", user.toString(), "pascoa", "Pago R$ 500,00 pelo bombom"));
        emailsCaixaEntrada.addEmail(new Email("Coelho", user.toString(), "Vendo bombom", "Vendo bombom R$ 250,00 ou 3 x 500,00"));
    }

    private void setDataTable(EmailData data){
        Email emailVazio = new Email("Vazio", user.toString(), "Vazio", "Vazio");
        tableEmails.setItems(data.getEmails());
        preencheEmail(data.getEmails().isEmpty() ? emailVazio : data.getEmails().get(0));
    }

    private void receberEmails(EmailData data){
        Mensagem mensagems[] = Talker.getInstance().getMensagens(user.toString());
        if (mensagems != null){
            for (Mensagem m : mensagems){
                Email e = new Email(m.getRemetente(), m.getDestinatario(), m.getAssunto(), m.getTexto());
                data.getEmails().add(e);
            }
        }else {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setContentText("Sem novas mensagens");
            alert.show();
        }
    }
}
