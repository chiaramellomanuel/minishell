#!/bin/bash

# Definizione delle variabili
SOURCE_DIR="$HOME/Documenti"
BACKUP_DIR="$HOME/Backup"
LOG_FILE="$HOME/backup.log"
ARCHIVE_NAME="backup_$(date +'%Y-%m-%d_%H-%M-%S').tar.gz"

# Creazione della cartella di backup se non esiste
mkdir -p "$BACKUP_DIR"

# Backup incrementale: copia solo file nuovi o modificati
rsync -av --delete "$SOURCE_DIR/" "$BACKUP_DIR/last/"

# Creazione di un archivio compresso dei file di backup
tar -czf "$BACKUP_DIR/$ARCHIVE_NAME" -C "$BACKUP_DIR/last" .

# Log del backup eseguito
echo "$(date +'%Y-%m-%d %H:%M:%S') - Backup creato: $ARCHIVE_NAME" >> "$LOG_FILE"

# Pulizia: Rimuove i backup più vecchi di 7 giorni
find "$BACKUP_DIR" -type f -name "backup_*.tar.gz" -mtime +7 -exec rm {} \;

# Messaggio di completamento
echo "Backup completato con successo: $ARCHIVE_NAME"
