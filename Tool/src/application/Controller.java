package application;

import java.io.IOException;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;

public class Controller {
	
	// **Declare static Stage**  
	private static Stage secondaryStage = new Stage(); 
	private void setSecondaryStage(Stage stage) {Controller.secondaryStage = stage;}
	static public Stage getPrimaryStage() {return Controller.secondaryStage;}
	
	@FXML
	public Button gen_em_but;

	public void initialize() throws IOException {
		Parent root = FXMLLoader.load(getClass().getResource("Sec.fxml")); 
		Scene scene = new Scene(root);
		secondaryStage.setScene(scene);
		scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
		secondaryStage.setTitle("Generator");
		secondaryStage.setScene(scene);
	}
	public void gen_em(ActionEvent e) {
		secondaryStage.show();
	}
	
}
