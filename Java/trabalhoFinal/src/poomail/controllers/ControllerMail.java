package poomail.controllers;

import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import poomail.Main;
import poomail.classes.*;
import poomail.data.Email;
import poomail.data.EmailData;
import poomail.data.User;
import poomail.holders.EmailHolder;
import poomail.holders.UserHolder;

import java.io.IOException;

import static java.lang.Thread.sleep;

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
    private Button btnDeletar;

    private EmailData emailsCaixaEntrada;
    private EmailData emailsEnviados;
    private EmailData emailsLixeira;
    private User user;
    private int countDown;



    @FXML
    public void initialize (){
        this.emailsCaixaEntrada = new EmailData();
        this.emailsEnviados = new EmailData();
        this.emailsLixeira = new EmailData();
        this.user = UserHolder.getInstance().getUser();
        this.countDown = 0;
        changeFocus();

        Task<Void> task = new Task<Void>() {
            @Override
            protected Void call() throws Exception {
                while (UserHolder.getInstance().getUser().isLoginValido()){
                    countDown--;
                    if (countDown <= 0) {
                        if (!Talker.getInstance().isConversando()) {
                            receberEmails(emailsCaixaEntrada, false);
                        }
                        countDown = 60;
                    }
                    sleep(1000);
                }
                return null;
            }
        };
        new Thread(task).start();
        setDataTable(emailsCaixaEntrada);
    }

    @FXML
    public void novoEmail(){
        EmailHolder.getINSTANCE().setEnviado(false);
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("scenes/novoEmail.fxml"));
            Parent root2 = fxmlLoader.load();
            Stage stage = new Stage();
            stage.setTitle("Novo Email");
            stage.setScene(new Scene(root2));
            stage.show();
            stage.getScene().getWindow().setOnHidden(e -> emailEnviado(EmailHolder.getINSTANCE().isEnviado(), stage));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    public void tableClicked(){
        preencheEmail(tableEmails.getSelectionModel().getSelectedItem());
    }


    @FXML
    public void atualizarEmail(){
        receberEmails(emailsCaixaEntrada, true);
        setDataTable(emailsCaixaEntrada);
        countDown = 60;
    }

    @FXML
    public void sairEmail(){
        UserHolder.getInstance().setUser(new User("Novo Usuario"));
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
        fieldPara.setText(email.getEmailPara());
        fieldDe.setText(email.getEmailDe());
        fieldTitulo.setText(email.getTitulo());
        areaConteudo.setWrapText(true);
        areaConteudo.setText(email.getConteudo());
    }


//    private void populaEmail(){
//        emailsCaixaEntrada.addEmail(new Email("JM", user.toString(), "Deu ruim", "Manda o nascimento pra brasilia"));
//        emailsCaixaEntrada.addEmail(new Email("LI", user.toString(), "Desconto", "Existe desconto no serviço de manicure para quem tem 9 dedos?"));
//        emailsCaixaEntrada.addEmail(new Email("Eneias", user.toString(), "pascoa", "Pago R$ 500,00 pelo bombom"));
//        emailsCaixaEntrada.addEmail(new Email("Coelho", user.toString(), "Vendo bombom", "Vendo bombom R$ 250,00 ou 3 x 500,00"));
//    }

    private void setDataTable(EmailData data){
        Email emailVazio = new Email("Vazio", user.toString(), "Vazio", "Vazio");
        tableEmails.setItems(data.getEmails());
        preencheEmail(data.getEmails().isEmpty() ? emailVazio : data.getEmails().get(0));
    }

    private void receberEmails(EmailData data, boolean showAlert){
        Talker.getInstance().toggleConversando();
        Mensagem[] mensagems = Talker.getInstance().getMensagens(user.toString());
        Talker.getInstance().toggleConversando();
        if (mensagems != null){
            data.clearList();
            for (Mensagem m : mensagems){
                Email e = new Email(m.getRemetente(), m.getDestinatario(), m.getAssunto(), m.getTexto());
                data.getEmails().add(e);
            }
        }else {
            if(showAlert){
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setContentText("Sem novas mensagens");
                alert.show();
            }
        }
    }

    private void emailEnviado(boolean enviado, Stage stage){
        if (enviado) {
            Email email = EmailHolder.getINSTANCE().getEmail();
            emailsEnviados.addEmail(email);
        }
        stage.close();
    }
}
