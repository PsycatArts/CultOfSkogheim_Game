// Fill out your copyright notice in the Description page of Project Settings.


#include "Skogheim/NPC/DialogueWidgetBase.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Components/TextBlock.h"
#include "Dom/JsonObject.h"

void UDialogueWidgetBase::SetOwningNPC(ANPC* InOwningNPC)                                                                       //set the NPC that this dialogue AI belongs to
{
    if (InOwningNPC != nullptr)                                                                             
    {
        OwningNPC = InOwningNPC;
        PersonalityComponent = Cast<UPersonalityComponent>(OwningNPC->GetComponentByClass(UPersonalityComponent::StaticClass()));
    }
}

                                                                                                                                //send HTTP Request to API
void UDialogueWidgetBase::SendApiRequest(const FString& PlayerInput)
{
   TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();                                                   //json object to create HTTP request 
   HttpRequest->SetHeader(TEXT("Authorization"), TEXT("API key"));           //OpenAI's API Key authentication 
   HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));                                                        
   HttpRequest->SetURL(TEXT("https://api.openai.com/v1/chat/completions"));                                                     //API endpoint URL
   HttpRequest->SetVerb(TEXT("POST"));                                                                                          //sending of data

   TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());                                                       //create json to hold data to send
   JsonObject->SetStringField(TEXT("model"), TEXT("gpt-3.5-turbo"));                                                            //current API AI Model gpt-3.5-turbo
   JsonObject->SetNumberField(TEXT("max_tokens"), 300);                                                                         //max length  of tokens (paid tokens)
   
   if (OwningNPC != nullptr) {                                                                                                  //set AI temperature
       JsonObject->SetNumberField(TEXT("temperature"), OwningNPC->temperature);
   }
   else {
       JsonObject->SetNumberField(TEXT("temperature"), 0.65);
   }

   TSharedPtr<FJsonObject> SystemRoleJson = MakeShareable(new FJsonObject());                                                   //create json for system, message, role.
   SystemRoleJson->SetStringField(TEXT("role"), TEXT("system"));
    if (PersonalityComponent!= NULL )
    {
       SystemRoleJson->SetStringField(TEXT("content"), PersonalityComponent->Prompt);                                           //set AI prompt (NPC personality)
    }
   else
   {
       return;                                                                                                              
   }

   TSharedPtr<FJsonObject> UserRoleJson = MakeShareable(new FJsonObject());                                                     //json that contains Player input
   UserRoleJson->SetStringField(TEXT("role"), TEXT("user"));
   UserRoleJson->SetStringField(TEXT("content"), PlayerInput);
                                    
   TArray<TSharedPtr<FJsonValue>> MessagesArray;                                                                                //array of message objects as expected by API
   MessagesArray.Add(MakeShareable(new FJsonValueObject(SystemRoleJson)));
   MessagesArray.Add(MakeShareable(new FJsonValueObject(UserRoleJson)));
   JsonObject->SetArrayField(TEXT("messages"), MessagesArray);
                                                                                                                                //request wrapup 
   FString OutputString;                                                                                                           
   TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
   FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);                                                                //serialize JSON into string
   HttpRequest->SetContentAsString(OutputString);                                                                               //send Json in HTTP request body                                                                          
   HttpRequest->OnProcessRequestComplete().BindUObject(this, &UDialogueWidgetBase::OnResponseReceived);                         //bind function to handle API response
   HttpRequest->ProcessRequest();                                                                                               //send request 
}

void UDialogueWidgetBase::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)               //receive AI response
{
    if (bWasSuccessful && Response.IsValid())
    {
        FString ResponseString = Response->GetContentAsString();                                                                    //get AI response as string
        TSharedPtr<FJsonObject> Json;                                                                           
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);                                            //deserialize response into a JSON object

        if (FJsonSerializer::Deserialize(Reader, Json) && Json.IsValid())                                                           
        {
            const TArray<TSharedPtr<FJsonValue>>* ChoicesArray;                                                                      //get choices array which contains NPC reply
            if (Json->TryGetArrayField(TEXT("choices"), ChoicesArray))
            {
                const TSharedPtr<FJsonObject>* ChoiceJson;                                                                           //get first object of choices array
                if ((*ChoicesArray)[0]->TryGetObject(ChoiceJson) && ChoiceJson != nullptr)
                {
                    TSharedPtr<FJsonObject> MessageObject = (*ChoiceJson)->GetObjectField(TEXT("message"));                          //extract message 
                    FString FinalContent;
                    if (MessageObject->TryGetStringField(TEXT("content"), FinalContent))                                             //extract content from message 
                    {
                        FinalContent = FinalContent.Replace(TEXT("\\n"), TEXT("\n")).Replace(TEXT("\\\""), TEXT("\""));              //replace unwanted characters
                        CurrentResponse = FinalContent;                                                                              //set repsponse 

                       
                        if (FinalContent.Split(TEXT("|"), &Emotion, &DialogueContent))                                               //EXTRACT EMOTION & DIALOGUE split string at | , save left part in emotion, right part in dialogueContent
                        {
                            Emotion = Emotion.TrimStartAndEnd();                                                                     //trim white space (spacebars)
                            DialogueContent = DialogueContent.TrimStartAndEnd();

                            CurrentResponse = DialogueContent;
                            
                            if (OwningNPC) 
                            {
                                for (const TPair<FString, bool>& KeywordPair : OwningNPC->KeywordList)                                //check for keywords (set Keyword true)
                                {
                                    if (CurrentResponse.Contains(KeywordPair.Key, ESearchCase::IgnoreCase))
                                    {
                                        OwningNPC->KeywordList[KeywordPair.Key] = true;
                                    }
                                }

                                if (PersonalityComponent)                                                                              //handle emotion
                                {
                                    
                                    PersonalityComponent->SetEmotion(Emotion);                                                          //set emotion itself                                 
                                    PersonalityComponent->SetStateFromEmotion(Emotion);                                                 //change state to the according emotion
                                    PersonalityComponent->SetResponse(CurrentResponse);                                                 //set response 

                                    PersonalityComponent->CheckKeywords(CurrentResponse);                                               //BP function

                                }
                            }
                        }
                        CreateText();                                                                                                   //call BP function to create text WBP to attach onto dialogue box to show the NPC response
                    }
                }
            }
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Json response failed"));
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("API request failed"));
    }
}

